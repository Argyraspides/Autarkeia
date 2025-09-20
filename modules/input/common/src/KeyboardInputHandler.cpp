//
// Created by gaugamela on 9/11/25.
//
#include "KeyboardInputHandler.hpp"
#include "InputPeripheralDetection.hpp"
#include <fcntl.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static constexpr int POLL_NEW_KEYBOARD_INTERVAL_MS = 3000;

static constexpr uint16_t KEY_RELEASED = 0;
static constexpr uint16_t KEY_PRESSED = 1;
static constexpr size_t MAX_KEY_PRESSED_BUF_SIZE = 128;

namespace InputCommon
{
KeyboardInputHandler::KeyboardInputHandler() noexcept
    : m_running( false ),
      m_keyboardInputThreads( std::vector< std::thread >() ),
      m_keyboardDetectionThread( std::thread() ),
      m_connectedKeyboards( InputCommon::KeyboardHashSet() ),
      m_lastPressedKeys( std::queue< KeyInputCode >() ),
      m_lastPressedKeysMutex( std::mutex() ),
      m_currentState( HandlerState::WaitingForKeyboard )
{
}

KeyboardInputHandler::~KeyboardInputHandler() noexcept
{
    Stop();
}

std::optional< KeyInputCode > KeyboardInputHandler::GetNextKeyPress()
{
    std::lock_guard< std::mutex > lastPressedKeysQueueLock( m_lastPressedKeysMutex );

    if ( m_keyboardException )
        std::rethrow_exception( m_keyboardException );

    if ( m_lastPressedKeys.empty() )
        return std::nullopt;

    KeyInputCode keyPressed = m_lastPressedKeys.front();
    m_lastPressedKeys.pop();

    return keyPressed;
}

void KeyboardInputHandler::Start()
{
    m_running = true;
    m_keyboardDetectionThread = std::thread( &KeyboardInputHandler::WaitForKeyboards, this );
}

void KeyboardInputHandler::Stop() noexcept
{
    m_running = false;

    m_keyboardDetectionThread.join();

    for ( std::thread& thread : m_keyboardInputThreads )
        thread.join();

}

void KeyboardInputHandler::ListenToKeyboard( InputCommon::KeyboardInfo keyboardInfo )
{
    // Keyboard might have been unplugged
    if ( access( keyboardInfo.eventDevicePath.c_str(), F_OK ) != 0 )
        return;

    if ( access( keyboardInfo.eventDevicePath.c_str(), R_OK ) != 0 )
        throw InputCommon::PeripheralInputException(
            "Unable to open input device file: " + keyboardInfo.eventDevicePath +
            ". Insufficient permissions. Please run program with sudo/give this program permission to access the "
            "device file." );

    int keyboardFd = open( keyboardInfo.eventDevicePath.c_str(), O_RDONLY );

    if ( keyboardFd < 0 )
    {
        close( keyboardFd );
        throw InputCommon::PeripheralInputException( "Unable to open device file " + keyboardInfo.eventDevicePath +
                                                     " ... cause unknown" );
    }

    struct input_event keyboardInputEvent{};
    while ( m_running )
    {
        ssize_t bytesRead = read( keyboardFd, reinterpret_cast< void* >( &keyboardInputEvent ), sizeof( input_event ) );

        if ( bytesRead < 0 && errno == ENODEV ) // Keyboard probs unplugged / dead
        {
            close( keyboardFd );
            return;
        }

        if ( bytesRead != sizeof( input_event ) )
            continue;

        if ( keyboardInputEvent.type != EV_KEY )
            continue;

        if ( keyboardInputEvent.value != KEY_PRESSED )
            continue;

        std::lock_guard< std::mutex > lastPressedKeysQueueLock( m_lastPressedKeysMutex );

        if ( m_lastPressedKeys.size() == MAX_KEY_PRESSED_BUF_SIZE )
            m_lastPressedKeys.pop();

        m_lastPressedKeys.push( keyboardInputEvent.code );
    }

    close( keyboardFd );
}

void KeyboardInputHandler::WaitForKeyboards()
{
    while ( m_running )
    {
        InputCommon::KeyboardHashSet connectedKeyboards;
        try
        {
            connectedKeyboards = InputPeripheralDetection::GetConnectedKeyboards();
        }
        catch ( InputCommon::PeripheralInputException& )
        {
            throw;
        }

        for ( const InputCommon::KeyboardInfo& keyboardInfo : connectedKeyboards )
        {
            if ( m_connectedKeyboards.find( keyboardInfo ) != m_connectedKeyboards.end() )
                continue;

            m_keyboardInputThreads.emplace_back( &KeyboardInputHandler::ListenToKeyboard, this, keyboardInfo );
            m_connectedKeyboards.insert( keyboardInfo );
        }

        std::this_thread::sleep_for( std::chrono::milliseconds( POLL_NEW_KEYBOARD_INTERVAL_MS ) );
    }
}

} // namespace InputCommon