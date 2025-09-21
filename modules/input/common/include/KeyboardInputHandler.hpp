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

/* TODO::ARGYRASPIDES() {
 *
 *      A bit of a fundamental design tension here. We throw exceptions if keyboard device files cannot be read on the
 *      reasoning that if a keyboard cannot be read from in the first place -- there is literally nothing the KeyboardInputHandler
 *      can do about it, so we throw. However a user may have multiple keyboards, where at least one keyboard might still be
 *      readable/detectable/parseable, in which case we probably dont want to throw an exception.
 *
 *      Think about this and fix later. In 99% of cases a user will only have one keyboard so not an urgent fix.
 *
 *      Also something a bit weird, different keyboard threads may throw an exception at the same time for different reasons, but you
 *      have only one exception pointer. Might be okay ... only downside is that we don't show all exceptions that occurred,
 *      just one.
 * }
 *
*/
namespace InputCommon
{

using KeyInputCode = size_t;
constexpr KeyInputCode InvalidKeyCode = std::numeric_limits< size_t >::max();

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
  try
  {
      KeyboardInputHandler handler;
      handler.Start();

      while (applicationRunning)
      {
          handler.WaitForKeyPress();
          auto key = handler.GetLastKeyPress();
          // Process key...
      }

      handler.Stop();
  }
  catch (const PeripheralInputE
xception& e)
  {
      // Handle keyboard system failures
  }
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
     * @brief Blocks the calling thread until a key press is available to take from the buffer
     */
    void WaitForKeyPress();

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
    void DetectKeyboards();

  private:
    std::atomic_bool m_running;

    std::vector< std::thread > m_keyboardInputThreads;
    std::thread m_keyboardDetectionThread;

    InputCommon::KeyboardHashSet m_connectedKeyboards;

    std::queue< KeyInputCode > m_lastPressedKeys;
    std::mutex m_lastPressedKeysMutex;

    InputCommon::PeripheralInputExceptionPtr m_keyboardException;
    std::mutex m_keyboardExceptionMutex;

    std::binary_semaphore m_waitForInputSemaphore;
};

} // namespace InputCommon

#endif // AUTARKEIA_KEYBOARDINPUTHANDLER_HPP
