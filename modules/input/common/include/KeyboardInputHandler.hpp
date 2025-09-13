//
// Created by gaugamela on 9/11/25.
//

#ifndef AUTARKEIA_KEYBOARDINPUTHANDLER_HPP
#define AUTARKEIA_KEYBOARDINPUTHANDLER_HPP

#include "KeyboardInfo.hpp"
#include <mutex>
#include <optional>
#include <queue>
#include <thread>

using KeyInputCode = size_t;

class KeyboardInputHandler
{
  public:
    KeyboardInputHandler();

    KeyInputCode GetLastKeyPress();
    std::string GetCurrentKeyboardName();

    void StartListening();
    void Stop();

  private:
    void ListenToKeyboard();
    void WaitForKeyboards();

  private:
    bool m_running;
    std::thread m_keyboardInputHandlerThread;

    std::vector< KeyboardInfo > m_connectedKeyboards;
    std::optional< KeyboardInfo > m_currentListeningKeyboard;

    std::queue< KeyInputCode > m_lastPressedKeys;
    std::mutex m_lastPressedKeysMutex;
};

#endif // AUTARKEIA_KEYBOARDINPUTHANDLER_HPP
