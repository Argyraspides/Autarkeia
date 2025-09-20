//
// Created by gaugamela on 9/11/25.
//

#ifndef AUTARKEIA_KEYBOARDINPUTHANDLER_HPP
#define AUTARKEIA_KEYBOARDINPUTHANDLER_HPP

#include "KeyboardInfo.hpp"
#include "PeripheralInputException.hpp"
#include <atomic>
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
    ListeningForInput,
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
     * @brief Returns the next key that the user pressed (the buffer is a queue), and consumes the event. The last key the user pressed
     * would be the key at the end of the queue. Use macros in linux/input-event-codes.h for checking which key was
     * pressed (prefixed with "KEY_").
     * @returns std::nullopt if no key has been pressed, otherwise KeyInputCode
     */
    std::optional< KeyInputCode > GetNextKeyPress();

    /**
     * @brief Starts the keyboard input handler on another thread. Automatically detects connected keyboards and begins
     * listening to key presses, adding them to the buffer
     * @throws PeripheralInputException thrown if it's impossible to listen to the keyboard or figure out if any are
     * connected
     */
    void Start();
    void Stop() noexcept;

  private:
    void ListenToKeyboard( InputCommon::KeyboardInfo );
    void WaitForKeyboards();

  private:
    std::atomic_bool m_running;

    std::vector< std::thread > m_keyboardInputThreads;
    std::thread m_keyboardDetectionThread;

    InputCommon::KeyboardHashSet m_connectedKeyboards;

    std::queue< KeyInputCode > m_lastPressedKeys;
    std::mutex m_lastPressedKeysMutex;
    std::mutex m_connectedKeyboardsMutex;

    InputCommon::PeripheralInputExceptionPtr m_keyboardException;
};

} // namespace InputCommon

#endif // AUTARKEIA_KEYBOARDINPUTHANDLER_HPP
