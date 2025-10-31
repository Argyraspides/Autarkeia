//
// Created by gaugamela on 9/11/25.
//
#include "KeyboardInputHandler.hpp"
#include "InputPeripheralDetection.hpp"
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
KeyboardInputHandler::KeyboardInputHandler() noexcept
    : m_running{ false },
      m_terminationSemaphore{ 0 }
{
}

KeyboardInputHandler::~KeyboardInputHandler() noexcept
{
    // Possible other threads will call GetNextKeyPress() in the middle of destruction -- wait
    // before destroying
    std::lock_guard< std::mutex > lastPressedKeysQueueLock( m_lastPressedKeysMutex );
    Stop();
}

std::optional< KeyInputCode > KeyboardInputHandler::GetNextKeyPress() noexcept
{
    std::optional< KeyInputCode > keyPressed = std::nullopt;

    {
        std::lock_guard< std::mutex > lastPressedKeysQueueLock( m_lastPressedKeysMutex );

        if ( m_lastPressedKeys.empty() )
            return std::nullopt;

        keyPressed = m_lastPressedKeys.front();
        m_lastPressedKeys.pop();
    }

    return keyPressed;
}

void KeyboardInputHandler::WaitForKeyPress() noexcept
{
    std::unique_lock< std::mutex > lastPressedKeysQueueLock( m_lastPressedKeysMutex );
    m_keysAvailableCv.wait( lastPressedKeysQueueLock,
                            [ this ]() -> bool { return !m_lastPressedKeys.empty() || !m_running; } );
}

void KeyboardInputHandler::Start() noexcept
{
    m_running = true;
    m_keyboardDetectionThread = std::thread( &KeyboardInputHandler::DetectKeyboards, this );

    int pipeCreateSuccess = pipe( s_terminationPipeFds );
    m_terminationThread = std::thread( &KeyboardInputHandler::StopListeningThreads, this );
}

void KeyboardInputHandler::Stop() noexcept
{

    m_running = false;

    m_keysAvailableCv.notify_all();

    m_terminationSemaphore.release();

    for ( std::thread& thread : m_keyboardInputThreads )
    {
        if ( !thread.joinable() )
            continue;

        thread.join();
    }

    if ( m_terminationThread.joinable() )
        m_terminationThread.join();

    if ( m_keyboardDetectionThread.joinable() )
        m_keyboardDetectionThread.join();

    close( s_terminationPipeFds[ PIPE_READ_IDX ] );
    close( s_terminationPipeFds[ PIPE_WRITE_IDX ] );
}

void KeyboardInputHandler::ListenToKeyboard( InputCommon::KeyboardInfo keyboardInfo ) noexcept
{
    // Keyboard might have been unplugged
    if ( access( keyboardInfo.eventDevicePath.c_str(), F_OK ) != 0 )
        return;

    if ( access( keyboardInfo.eventDevicePath.c_str(), R_OK ) != 0 )
    {
        // TODO::LATER::ARGYRASPIDES() { Replace with error logging class later }
        std::cout << "Unable to open input device file for keyboard " << keyboardInfo.keyboardName
                  << " with device file at " << keyboardInfo.eventDevicePath
                  << ". Insufficient permissions. Please run program with "
                     "sudo/give this program permission to access the "
                     "device file."
                  << std::endl;
        return;
    }

    int keyboardFd = open( keyboardInfo.eventDevicePath.c_str(), O_RDONLY );

    if ( keyboardFd < 0 )
    {
        close( keyboardFd );
        // TODO::LATER::ARGYRASPIDES() { Replace with error logging class later }
        std::cout << "Unable to open device file " + keyboardInfo.eventDevicePath + " ... cause unknown" << std::endl;
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
            std::lock_guard< std::mutex > lastPressedKeysQueueLock( m_lastPressedKeysMutex );

            if ( m_lastPressedKeys.size() == MAX_KEY_PRESSED_BUF_SIZE )
                m_lastPressedKeys.pop();

            m_lastPressedKeys.push( keyboardInputEvent.code );
        }

        m_keysAvailableCv.notify_all();
    }

    close( keyboardFd );
}

void KeyboardInputHandler::StopListeningThreads() noexcept
{
    m_terminationSemaphore.acquire();
    // We just need to write to the fd to unblock the other threads on their
    // read() syscalls so we just need to write something, anything at all
    char writeCancel = 'c';
    write( s_terminationPipeFds[ PIPE_WRITE_IDX ], static_cast< void* >( &writeCancel ), 1 );
}

void KeyboardInputHandler::DetectKeyboards() noexcept
{
    while ( m_running )
    {
        InputCommon::KeyboardHashSet connectedKeyboards;
        try
        {
            connectedKeyboards = InputPeripheralDetection::GetConnectedKeyboards();
        }
        catch ( InputCommon::PeripheralInputException& pie )
        {
            // TODO::LATER::ARGYRASPIDES() { Replace with error logging class later }
            std::cout << pie.what() << "\n";
        }

        for ( const InputCommon::KeyboardInfo& keyboardInfo : connectedKeyboards )
        {
            if ( m_connectedKeyboards.find( keyboardInfo ) != m_connectedKeyboards.end() )
                continue;

            m_keyboardInputThreads.emplace_back( &KeyboardInputHandler::ListenToKeyboard, this, keyboardInfo );
            m_connectedKeyboards.insert( keyboardInfo );
        }

        for ( auto it = m_connectedKeyboards.begin(); it != m_connectedKeyboards.end(); )
        {
            if ( access( it->eventDevicePath.c_str(), F_OK | R_OK ) != 0 )
                it = m_connectedKeyboards.erase( it );
            else
                ++it;
        }

        std::this_thread::sleep_for( std::chrono::milliseconds( POLL_NEW_KEYBOARD_INTERVAL_MS ) );
    }
}

} // namespace InputCommon