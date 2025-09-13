//
// Created by gaugamela on 9/11/25.
//
#include "KeyboardInputHandler.hpp"
#include "PeripheralDetector.hpp"
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

KeyboardInputHandler::KeyboardInputHandler()
    : m_running( false ),
      m_keyboardInputHandlerThread( std::thread() ),
      m_connectedKeyboards( std::nullopt ),
      m_lastPressedKeys( std::queue< KeyInputCode >() ),
      m_lastPressedKeysMutex( std::mutex() )
{
}

KeyInputCode KeyboardInputHandler::GetLastKeyPress()
{
    std::lock_guard< std::mutex > lastPressedKeysQueueLock( m_lastPressedKeysMutex );

    if ( m_lastPressedKeys.empty() )
        return KEY_CNT;

    KeyInputCode keyPressed = m_lastPressedKeys.front();
    m_lastPressedKeys.pop();

    return keyPressed;
}

std::optional< std::string > KeyboardInputHandler::GetCurrentKeyboardName()
{
    if ( m_currentListeningKeyboard.has_value() )
        return m_currentListeningKeyboard.value().keyboardName;

    return std::nullopt;
}

void KeyboardInputHandler::StartListening()
{
    m_running = true;

    m_keyboardInputHandlerThread = std::thread( &KeyboardInputHandler::WaitForKeyboards, this );

    m_keyboardInputHandlerThread.join();

    m_keyboardInputHandlerThread = std::thread( &KeyboardInputHandler::ListenToKeyboard, this );
}

void KeyboardInputHandler::Stop()
{
    m_running = false;

    if ( m_keyboardInputHandlerThread.joinable() )
        m_keyboardInputHandlerThread.join();
}

void KeyboardInputHandler::ListenToKeyboard()
{
    if ( !m_connectedKeyboards.has_value() )
        return;

    if ( m_connectedKeyboards.value().empty() )
        return;

    m_currentListeningKeyboard = m_connectedKeyboards.value().front();

    // Keyboard might have been unplugged
    if ( access( m_currentListeningKeyboard.value().eventDevicePath.c_str(), F_OK ) != 0 )
        return;

    if ( access( m_currentListeningKeyboard.value().eventDevicePath.c_str(), R_OK ) != 0 )
        throw std::runtime_error( "Unable to open input character device: " +
                                  m_currentListeningKeyboard.value().eventDevicePath + " insufficient permissions" );

    int keyboardFd = open( m_currentListeningKeyboard.value().eventDevicePath.c_str(), O_RDONLY );

    if ( keyboardFd < 0 )
    {
        close( keyboardFd );
        throw std::runtime_error( "Unable to open input character device: " +
                          m_currentListeningKeyboard.value().eventDevicePath + " ... cause unknown");
    }

    struct input_event keyboardInputEvent{};
    while ( m_running )
    {
        ssize_t bytesRead = read( keyboardFd, reinterpret_cast< void* >( &keyboardInputEvent ), sizeof( input_event ) );

        if ( bytesRead < 0 && errno == ENODEV ) // Keyboard probs unplugged / dead
        {
            close(keyboardFd);
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
        m_connectedKeyboards = PeripheralDetector::GetConnectedKeyboards();

        if ( m_connectedKeyboards.has_value() || m_connectedKeyboards.value().empty() )
            break;

        std::this_thread::sleep_for( std::chrono::milliseconds( POLL_NEW_KEYBOARD_INTERVAL_MS ) );
    }
}