//
// Created by gaugamela on 9/11/25.
//
#include "KeyboardInputHandler.hpp"
#include "PeripheralDetector.hpp"
#include <iostream>
#include <linux/input.h>

static constexpr int POLL_NEW_KEYBOARD_INTERVAL_MS = 3000;

static constexpr uint16_t KEY_RELEASED = 0;
static constexpr uint16_t KEY_PRESSED = 1;
static constexpr size_t MAX_KEY_PRESSED_BUF_SIZE = 128;

KeyboardInputHandler::KeyboardInputHandler()
    : m_running( false ),
      m_keyboardInputHandlerThread( std::thread() ),
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
    if (m_currentListeningKeyboard.has_value())
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
    if ( !m_connectedKeyboards.has_value() || m_connectedKeyboards.value().empty() )
        return;

    m_currentListeningKeyboard = m_connectedKeyboards.value().front();
    std::ifstream inputCharDev( m_currentListeningKeyboard.value().eventDevicePath );

    if ( !inputCharDev.is_open() )
        throw std::ios_base::failure("Unable to open input character device: " + m_currentListeningKeyboard.value().eventDevicePath );

    struct input_event keyboardInputEvent{};
    while ( m_running )
    {
        if ( !inputCharDev.read( reinterpret_cast< char* >( &keyboardInputEvent ), sizeof( input_event ) ) )
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
}

void KeyboardInputHandler::WaitForKeyboards()
{
    while ( m_running )
    {
        m_connectedKeyboards = PeripheralDetector::GetConnectedKeyboards();

        if ( !m_connectedKeyboards.has_value() || m_connectedKeyboards.value().empty() )
            break;

        std::this_thread::sleep_for( std::chrono::milliseconds( POLL_NEW_KEYBOARD_INTERVAL_MS ) );
    }
}