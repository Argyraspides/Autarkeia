//
// Created by gaugamela on 9/11/25.
//

#ifndef AUTARKEIA_KEYBOARDINPUTHANDLER_HPP
#define AUTARKEIA_KEYBOARDINPUTHANDLER_HPP

#include "KeyboardInfo.hpp"
#include <atomic>
#include <mutex>
#include <optional>
#include <queue>
#include <thread>

using KeyInputCode = size_t;

enum class HandlerState
{
    WaitingForKeyboard,
    ListeningForInput
};

class KeyboardInputHandler
{
  public:
    KeyboardInputHandler();

    KeyInputCode GetLastKeyPress();
    std::optional< std::string > GetCurrentKeyboardName();

    /**
     * @brief Starts the keyboard input handler. Automatically detects connected keyboards and begins listening
     * to key presses, adding them to the buffer
     * @throws PeripheralInputException thrown if it's impossible to listen to the keyboard or figure out if any are connected
     */
    void Start();
    void Stop();

  private:
    void ListenToKeyboard();
    void WaitForKeyboards();
    void HandleStates();

  private:
    std::atomic_bool m_running;
    std::thread m_keyboardInputHandlerThread;

    std::optional< std::vector< KeyboardInfo > > m_connectedKeyboards;
    std::optional< KeyboardInfo > m_currentListeningKeyboard;

    std::queue< KeyInputCode > m_lastPressedKeys;
    std::mutex m_lastPressedKeysMutex;

    HandlerState m_currentState;
    std::exception_ptr m_keyboardException;
};

#endif // AUTARKEIA_KEYBOARDINPUTHANDLER_HPP
