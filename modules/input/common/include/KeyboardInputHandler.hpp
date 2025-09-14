//
// Created by gaugamela on 9/11/25.
//

#ifndef AUTARKEIA_KEYBOARDINPUTHANDLER_HPP
#define AUTARKEIA_KEYBOARDINPUTHANDLER_HPP

#include "KeyboardInfo.hpp"
#include "PeripheralInputException.hpp"
#include <atomic>
#include <linux/input-event-codes.h>
#include <mutex>
#include <optional>
#include <queue>
#include <thread>

namespace InputCommon
{

using KeyInputCode = size_t;

enum class HandlerState
{
    WaitingForKeyboard,
    ListeningForInput
};

/**
 * @brief KeyboardInputHandler automatically detects connected keyboards and begins listening to key presses.
 * For safety, you should ensure the entire lifecycle of the object (the moment Start() is called) is contained in a
 * try/catch block. KeyboardInputHandler relies on certain Linux device files to be both present and readable, which can
 * change at any arbitrary time. See the KeyboardInputHandler::Start() function description.
 *
 * Example use:
 *
 * @code
 * try
 * {
 *     KeyboardInputHandler handler;
 *     handler.Start();
 *
 *     while (applicationRunning)
 *     {
 *         auto key = handler.GetLastKeyPress();
 *         // Process key...
 *     }
 *
 *     handler.Stop();
 * }
 * catch (const PeripheralInputException& e)
 * {
 *     // Handle keyboard system failures
 * }
 * @endcode
 */
class KeyboardInputHandler
{
  public:
    KeyboardInputHandler() noexcept;
    ~KeyboardInputHandler() noexcept;

    /**
     * @brief Returns the next key that the user pressed (the buffer is a queue). The last key the user pressed
     * would be the key at the end of the queue. Use macros in linux/input-event-codes.h for checking which key was
     * pressed (prefixed with "KEY_")
     */
    KeyInputCode GetNextKeyPress() noexcept;
    std::optional< std::string > GetCurrentKeyboardName() noexcept;

    /**
     * @brief Starts the keyboard input handler on another thread. Automatically detects connected keyboards and begins
     * listening to key presses, adding them to the buffer
     * @throws PeripheralInputException thrown if it's impossible to listen to the keyboard or figure out if any are
     * connected
     */
    void Start();
    void Stop() noexcept;

  private:
    void ListenToKeyboard();
    void WaitForKeyboards();
    void HandleStates();

  private:
    std::atomic_bool m_running;
    std::thread m_keyboardInputHandlerThread;

    std::optional< std::vector< InputCommon::KeyboardInfo > > m_connectedKeyboards;
    std::optional< InputCommon::KeyboardInfo > m_currentListeningKeyboard;

    std::queue< KeyInputCode > m_lastPressedKeys;
    std::mutex m_lastPressedKeysMutex;

    HandlerState m_currentState;
    InputCommon::PeripheralInputExceptionPtr m_keyboardException;
};

}

#endif // AUTARKEIA_KEYBOARDINPUTHANDLER_HPP
