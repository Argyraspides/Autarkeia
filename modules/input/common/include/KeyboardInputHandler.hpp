//
// Created by gaugamela on 9/11/25.
//

#ifndef AUTARKEIA_KEYBOARDINPUTHANDLER_HPP
#define AUTARKEIA_KEYBOARDINPUTHANDLER_HPP

#include "KeyboardInfo.hpp"
#include <cstddef>
#include <mutex>
#include <optional>
#include <queue>
#include <thread>

using KeyInput = size_t;

class KeyboardInputHandler
{
  public:
    KeyboardInputHandler();

    KeyInput GetLastKeyPress();
    std::string GetCurrentKeyboardName();

    void StartListening();
    void Stop();

  private:
    void ListenToKeyboard();
    void WaitForKeyboards();

  private:
    bool m_running;
    std::thread m_keyboardInputHandlerThread;

    std::optional< std::vector< KeyboardInfo > > m_connectedKeyboards;
    std::optional< KeyboardInfo > m_currentListeningKeyboard;

    std::queue< KeyInput > m_lastPressedKeys;
    std::mutex m_lastPressedKeysMutex;
};

#endif // AUTARKEIA_KEYBOARDINPUTHANDLER_HPP
