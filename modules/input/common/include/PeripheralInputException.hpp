//
// Created by gaugamela on 9/14/25.
//

#ifndef AUTARKEIA_KEYBOARDEXCEPTION_HPP
#define AUTARKEIA_KEYBOARDEXCEPTION_HPP

#include <exception>
#include <string>

namespace InputCommon
{

/**
 * @brief PeripheralInputException should be thrown if:
 *      1: The file /proc/bus/input/devices, used for detecting connected peripherals, doesn't exist. Either because
 *          1a: We have insufficient permissions to open for reading (program must re-run as sudo)
 *          1b: File cannot be opened for another unknown reason
 *      2: The file associated with the peripheral (usually /dev/eventN) cannot be opened (usually due to insufficient
 * permissions)
 */

using PeripheralInputExceptionPtr = std::exception_ptr;
class PeripheralInputException : public std::exception
{
  public:
    explicit PeripheralInputException( const std::string& exceptionMsg )
        : m_exceptionMsg( exceptionMsg ) {};

    const char* what() const noexcept override
    {
        return m_exceptionMsg.c_str();
    }

  private:
    const std::string m_exceptionMsg;
};

} // namespace InputCommon

#endif // AUTARKEIA_KEYBOARDEXCEPTION_HPP
