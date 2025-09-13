//
// Created by gaugamela on 9/11/25.
//

#ifndef AUTARKEIA_PERIPHERALDETECTOR_HPP
#define AUTARKEIA_PERIPHERALDETECTOR_HPP

#include "KeyboardInfo.hpp"
#include <fstream>
#include <optional>
#include <string>

/**
 * @brief Detects peripherals connected on Linux systems by opening /proc/bus/input/devices and reading its contents
 */
namespace PeripheralDetector
{

bool IsKeyboard( const std::string& deviceFileEntry );

std::optional< std::string > GetDeviceName( const std::string& deviceFileEntry );

std::optional< std::string > GetEventDeviceName( const std::string& deviceFileEntry );

std::optional< std::vector< KeyboardInfo > > GetConnectedKeyboards();

} // namespace PeripheralDetector

#endif // AUTARKEIA_PERIPHERALDETECTOR_HPP
