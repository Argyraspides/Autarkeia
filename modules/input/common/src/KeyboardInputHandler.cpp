//
// Created by gaugamela on 9/11/25.
//
#include "KeyboardInputHandler.hpp"
#include "InputPeripheralDetection.hpp"
#include <fcntl.h>
#include <iostream>
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
      m_keyboardInputHandlerThread( std::thread() ),
      m_connectedKeyboards( std::nullopt ),
      m_lastPressedKeys( std::queue< KeyInputCode >() ),
      m_lastPressedKeysMutex( std::mutex() ),
      m_currentState( HandlerState::WaitingForKeyboard )
{
}

KeyboardInputHandler::~KeyboardInputHandler() noexcept
{
    Stop();
}

std::optional< KeyInputCode > KeyboardInputHandler::GetNextKeyPress() noexcept
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

std::optional< std::string > KeyboardInputHandler::GetCurrentKeyboardName() noexcept
{
    if ( m_currentListeningKeyboard.has_value() )
        return m_currentListeningKeyboard.value().keyboardName;

    return std::nullopt;
}

void KeyboardInputHandler::Start()
{
    m_running = true;
    m_keyboardInputHandlerThread = std::thread( &KeyboardInputHandler::HandleStates, this );
}

void KeyboardInputHandler::Stop() noexcept
{
    m_running = false;

    if ( m_keyboardInputHandlerThread.joinable() )
        m_keyboardInputHandlerThread.join();
}

void KeyboardInputHandler::ListenToKeyboard()
{
    if ( !m_connectedKeyboards.has_value() || m_connectedKeyboards.value().empty() )
    {
        m_currentState = HandlerState::WaitingForKeyboard;
        return;
    }

    m_currentListeningKeyboard = m_connectedKeyboards.value().front();

    // Keyboard might have been unplugged
    if ( access( m_currentListeningKeyboard.value().eventDevicePath.c_str(), F_OK ) != 0 )
    {
        m_currentState = HandlerState::WaitingForKeyboard;
        return;
    }

    if ( access( m_currentListeningKeyboard.value().eventDevicePath.c_str(), R_OK ) != 0 )
        throw InputCommon::PeripheralInputException(
            "Unable to open input device file: " + m_currentListeningKeyboard.value().eventDevicePath +
            ". Insufficient permissions. Please run program with sudo/give this program permission to access the "
            "device file." );

    int keyboardFd = open( m_currentListeningKeyboard.value().eventDevicePath.c_str(), O_RDONLY );

    if ( keyboardFd < 0 )
    {
        close( keyboardFd );
        throw InputCommon::PeripheralInputException(
            "Unable to open device file " + m_currentListeningKeyboard.value().eventDevicePath + " ... cause unknown" );
    }

    struct input_event keyboardInputEvent{};
    while ( m_running )
    {
        ssize_t bytesRead = read( keyboardFd, reinterpret_cast< void* >( &keyboardInputEvent ), sizeof( input_event ) );

        if ( bytesRead < 0 && errno == ENODEV ) // Keyboard probs unplugged / dead
        {
            close( keyboardFd );
            m_currentState = HandlerState::WaitingForKeyboard;
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
        try
        {
            m_connectedKeyboards = InputPeripheralDetection::GetConnectedKeyboards();
        }
        catch ( InputCommon::PeripheralInputException& )
        {
            throw;
        }

        if ( m_connectedKeyboards.has_value() || m_connectedKeyboards.value().empty() )
        {
            m_currentState = HandlerState::ListeningForInput;
            return;
        }

        std::this_thread::sleep_for( std::chrono::milliseconds( POLL_NEW_KEYBOARD_INTERVAL_MS ) );
    }
}

void KeyboardInputHandler::HandleStates()
{
    while ( m_running )
    {
        try
        {
            switch ( m_currentState )
            {
            case HandlerState::WaitingForKeyboard:
                WaitForKeyboards();
                break;
            case HandlerState::ListeningForInput:
                ListenToKeyboard();
                break;
            default:;
            }
        }
        catch ( InputCommon::PeripheralInputException& )
        {
            m_keyboardException = std::current_exception();
            return;
        }
    }
}

} // namespace InputCommon