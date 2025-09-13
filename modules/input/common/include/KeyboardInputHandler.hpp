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

    void StartListening();
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
};

#endif // AUTARKEIA_KEYBOARDINPUTHANDLER_HPP
