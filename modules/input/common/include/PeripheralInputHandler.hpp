//
// Created by gaugamela on 9/11/25.
//

#ifndef AUTARKEIA_PeripheralInputHandler_HPP
#define AUTARKEIA_PeripheralInputHandler_HPP

#include "PeripheralInfo.hpp"
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <optional>
#include <queue>
#include <semaphore>
#include <thread>

namespace InputCommon
{

using KeyInputCode = size_t;

/**
 * @brief PeripheralInputHandler automatically detects connected peripherals and begins listening to inputs.
 * PeripheralInputHandler relies on certain Linux device files to be both present and readable, which can
 * change at any arbitrary time. See the PeripheralInputHandler::Start() function description.
 *
 * Example use:
 *
 * @code
 *
 *     PeripheralInputHandler handler;
 *     handler.Start();
 *
 *     while (applicationRunning)
 *     {
 *         handler.WaitForKeyPress();
 *         auto key = handler.GetNextEvent();
 *         // Do something with the key
 *     }
 *
 *     handler.Stop();
 * @endcode
 */
class PeripheralInputHandler
{
  public:
    PeripheralInputHandler() noexcept;
    ~PeripheralInputHandler() noexcept;

    /**
     * @brief Returns the next key that the user pressed (the buffer is a queue), and consumes the event. The last key
     * the user pressed would be the key at the end of the queue. Use macros in linux/input-event-codes.h for checking
     * which key was pressed (prefixed with "KEY_").
     * @returns std::nullopt if no key has been pressed, otherwise KeyInputCode
     */
    std::optional< KeyInputCode > GetNextEvent() noexcept;

    /**
     * @brief Blocks the calling thread until a key press is available to take from the buffer
     */
    void WaitForEvent() noexcept;

    /**
     * @brief Starts the keyboard input handler on another thread. Automatically detects connected keyboards and begins
     * listening to key presses, adding them to the buffer
     * @throws PeripheralInputException thrown if it's impossible to listen to the keyboard or figure out if any are
     * connected
     */
    void Start() noexcept;
    void Stop() noexcept;

  private:
    void ListenToPeripheral( InputCommon::PeripheralInfo ) noexcept;
    void StopListeningThreads() noexcept;
    void DetectPeripherals() noexcept;

  private:
    std::atomic_bool m_running;

    std::vector< std::thread > m_peripheralInputThreads;
    std::thread m_peripheralDetectionThread;

    std::thread m_terminationThread;
    std::binary_semaphore m_terminationSemaphore;

    InputCommon::PeripheralHashSet m_connectedPeripherals;

    std::queue< KeyInputCode > m_lastObservedInputs;
    std::mutex m_lastObservedInputsMutex;
    std::condition_variable m_eventsAvailableCv;
};

} // namespace InputCommon

#endif // AUTARKEIA_PeripheralInputHandler_HPP
