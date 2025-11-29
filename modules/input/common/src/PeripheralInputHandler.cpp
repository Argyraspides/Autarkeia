//
// Created by gaugamela on 9/11/25.
//
#include "PeripheralInputHandler.hpp"
#include "InputPeripheralDetection.hpp"
#include "PeripheralInputException.hpp"
#include <algorithm>
#include <fcntl.h>
#include <iostream>
#include <linux/input.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static constexpr int POLL_NEW_KEYBOARD_INTERVAL_MS = 3000;
static constexpr size_t MAX_KEY_PRESSED_BUF_SIZE = 128;

static constexpr uint16_t KEY_HELD = 2;
static constexpr uint16_t KEY_RELEASED = 0;
static constexpr uint16_t KEY_PRESSED = 1;

static constexpr int PIPE_READ_IDX = 0;
static constexpr int PIPE_WRITE_IDX = 1;

static int s_terminationPipeFds[ 2 ];

namespace InputCommon
{
PeripheralInputHandler::PeripheralInputHandler() noexcept
    : m_running{ false },
      m_terminationSemaphore{ 0 }
{
}

PeripheralInputHandler::~PeripheralInputHandler() noexcept
{
    // Possible other threads will call GetNextKeyPress() in the middle of destruction -- wait
    // before destroying
    std::lock_guard< std::mutex > lastPressedKeysQueueLock( m_lastObservedInputsMutex );
    Stop();
}

std::optional< KeyInputCode > PeripheralInputHandler::GetNextEvent() noexcept
{
    std::optional< KeyInputCode > keyPressed = std::nullopt;

    {
        std::lock_guard< std::mutex > lastPressedKeysQueueLock( m_lastObservedInputsMutex );

        if ( m_lastObservedInputs.empty() )
            return std::nullopt;

        keyPressed = m_lastObservedInputs.front();
        m_lastObservedInputs.pop();
    }

    return keyPressed;
}

void PeripheralInputHandler::WaitForEvent() noexcept
{
    std::unique_lock< std::mutex > lastPressedKeysQueueLock( m_lastObservedInputsMutex );
    m_eventsAvailableCv.wait( lastPressedKeysQueueLock,
                            [ this ]() -> bool { return !m_lastObservedInputs.empty() || !m_running; } );
}

void PeripheralInputHandler::Start() noexcept
{
    m_running = true;
    m_peripheralDetectionThread = std::thread( &PeripheralInputHandler::DetectPeripherals, this );

    int pipeCreateSuccess = pipe( s_terminationPipeFds );
    m_terminationThread = std::thread( &PeripheralInputHandler::StopListeningThreads, this );
}

void PeripheralInputHandler::Stop() noexcept
{

    m_running = false;

    m_eventsAvailableCv.notify_all();

    m_terminationSemaphore.release();

    for ( std::thread& thread : m_peripheralInputThreads )
    {
        if ( !thread.joinable() )
            continue;

        thread.join();
    }

    if ( m_terminationThread.joinable() )
        m_terminationThread.join();

    if ( m_peripheralDetectionThread.joinable() )
        m_peripheralDetectionThread.join();

    close( s_terminationPipeFds[ PIPE_READ_IDX ] );
    close( s_terminationPipeFds[ PIPE_WRITE_IDX ] );
}

void PeripheralInputHandler::ListenToPeripheral( InputCommon::PeripheralInfo PeripheralInfo ) noexcept
{
    // Keyboard might have been unplugged
    if ( access( PeripheralInfo.eventDevicePath.c_str(), F_OK ) != 0 )
        return;

    if ( access( PeripheralInfo.eventDevicePath.c_str(), R_OK ) != 0 )
    {
        // TODO::LATER::ARGYRASPIDES() { Replace with error logging class later }
        std::cout << "Unable to open input device file for keyboard " << PeripheralInfo.peripheralName
                  << " with device file at " << PeripheralInfo.eventDevicePath
                  << ". Insufficient permissions. Please run program with "
                     "sudo/give this program permission to access the "
                     "device file."
                  << std::endl;
        return;
    }

    int keyboardFd = open( PeripheralInfo.eventDevicePath.c_str(), O_RDONLY );

    if ( keyboardFd < 0 )
    {
        close( keyboardFd );
        // TODO::LATER::ARGYRASPIDES() { Replace with error logging class later }
        std::cout << "Unable to open device file " + PeripheralInfo.eventDevicePath + " ... cause unknown" << std::endl;
        return;
    }

    // nfds -> check man pages for select() syscall
    int nfds = std::max( { keyboardFd, s_terminationPipeFds[ PIPE_READ_IDX ] } ) + 1;

    fd_set fdSet;
    FD_ZERO( &fdSet );
    FD_SET( s_terminationPipeFds[ PIPE_READ_IDX ], &fdSet );
    FD_SET( keyboardFd, &fdSet );

    struct input_event keyboardInputEvent{};
    while ( m_running )
    {
        // To prevent being blocked on read syscall forever, we will wait for both the keyboard and also the
        // s_terminationPipe. A termination thread will write to the s_terminationPipe to artifically wake us up so we
        // can exit the while loop
        int selectSuccess = select( nfds, &fdSet, NULL, NULL, NULL );

        if ( selectSuccess < 0 )
            break;

        ssize_t bytesRead = -1;
        if ( FD_ISSET( keyboardFd, &fdSet ) )
            bytesRead = read( keyboardFd, reinterpret_cast< void* >( &keyboardInputEvent ), sizeof( input_event ) );
        else if ( FD_ISSET( s_terminationPipeFds[ PIPE_READ_IDX ], &fdSet ) )
            break;

        if ( bytesRead < 0 && errno == ENODEV ) // Keyboard probs unplugged / dead
            break;

        if ( bytesRead != sizeof( input_event ) )
            continue;

        if ( keyboardInputEvent.type != EV_KEY )
            continue;

        // BEWARE::ARGYRASPIDES() { BEHAVIOR TO ONLY LISTEN TO KEY PRESSES/HOLDS, NOT RELEASES }
        if ( keyboardInputEvent.value == KEY_RELEASED )
            continue;

        {
            std::lock_guard< std::mutex > lastPressedKeysQueueLock( m_lastObservedInputsMutex );

            if ( m_lastObservedInputs.size() == MAX_KEY_PRESSED_BUF_SIZE )
                m_lastObservedInputs.pop();

            m_lastObservedInputs.push( keyboardInputEvent.code );
        }

        m_eventsAvailableCv.notify_all();
    }

    close( keyboardFd );
}

void PeripheralInputHandler::StopListeningThreads() noexcept
{
    m_terminationSemaphore.acquire();
    // We just need to write to the fd to unblock the other threads on their
    // read() syscalls so we just need to write something, anything at all
    char writeCancel = 'c';
    write( s_terminationPipeFds[ PIPE_WRITE_IDX ], static_cast< void* >( &writeCancel ), 1 );
}

void PeripheralInputHandler::DetectPeripherals() noexcept
{
    while ( m_running )
    {
        InputCommon::PeripheralHashSet connectedKeyboards;
        try
        {
            connectedKeyboards = InputPeripheralDetection::GetConnectedKeyboards();
        }
        catch ( InputCommon::PeripheralInputException& pie )
        {
            // TODO::LATER::ARGYRASPIDES() { Replace with error logging class later }
            std::cout << pie.what() << "\n";
        }

        for ( const InputCommon::PeripheralInfo& PeripheralInfo : connectedKeyboards )
        {
            if ( m_connectedPeripherals.find( PeripheralInfo ) != m_connectedPeripherals.end() )
                continue;

            m_peripheralInputThreads.emplace_back( &PeripheralInputHandler::ListenToPeripheral, this, PeripheralInfo );
            m_connectedPeripherals.insert( PeripheralInfo );
        }

        for ( auto it = m_connectedPeripherals.begin(); it != m_connectedPeripherals.end(); )
        {
            if ( access( it->eventDevicePath.c_str(), F_OK | R_OK ) != 0 )
                it = m_connectedPeripherals.erase( it );
            else
                ++it;
        }

        std::this_thread::sleep_for( std::chrono::milliseconds( POLL_NEW_KEYBOARD_INTERVAL_MS ) );
    }
}

} // namespace InputCommon