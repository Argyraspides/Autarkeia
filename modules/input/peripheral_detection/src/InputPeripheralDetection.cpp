//
// Created by gaugamela on 9/11/25.
//
#include "InputPeripheralDetection.hpp"
#include "PeripheralInputException.hpp"
#include <cstdint>
#include <iostream>
#include <fstream>
#include <linux/input-event-codes.h>
#include <sstream>
#include <unistd.h>

/*
                Example of an entry for a Logitech mouse under /proc/bus/input/devices:

I: Bus=0003 Vendor=046d Product=c077 Version=0111
N: Name="Logitech USB Optical Mouse"
P: Phys=usb-0000:05:00.4-2/input0
S: Sysfs=/devices/pci0000:00/0000:00:08.1/0000:05:00.4/usb3/3-2/3-2:1.0/0003:046D:C077.0005/input/input21
U: Uniq=
H: Handlers=mouse2 event17
B: PROP=0
B: EV=17
B: KEY=70000 0 0 0 0
B: REL=903
B: MSC=10


                Example of an entry for a keyboard under /proc/bus/input/devices:

I: Bus=0003 Vendor=048d Product=c965 Version=0110
N: Name="ITE Tech. Inc. ITE Device(8295) Keyboard"
P: Phys=usb-0000:05:00.4-3/input0
S: Sysfs=/devices/pci0000:00/0000:00:08.1/0000:05:00.4/usb3/3-3/3-3:1.0/0003:048D:C965.0002/input/input11
U: Uniq=
H: Handlers=sysrq kbd event7 leds
B: PROP=0
B: EV=120013
B: KEY=1000000000007 ff9f207ac14057ff febeffdfffefffff fffffffffffffffe
B: MSC=10
B: LED=1f

*/

static const inline std::string EV_START_LINE = "B: EV=";
static const inline std::string KEY_START_LINE = "B: KEY=";
static const inline std::string NAME_START_LINE = "N: Name=";
static const inline std::string HANDLERS_START_LINE = "H: Handlers=";
static const inline std::string MOUSE_HANDLERS_ENTRY = "mouse";

static const inline std::string DEVICE_FILE_INFO_PATH = "/proc/bus/input/devices";
static const inline std::string DEVICE_FILE_INTERFACE_PREFIX_PATH = "/dev/input";

static inline std::string EVENT_DEVICE_FILE_PREFIX_NAME = "event";

namespace InputPeripheralDetection
{
bool IsKeyboard( const std::string& deviceFileEntry ) noexcept
{
    if ( deviceFileEntry.empty() )
        return false;

    std::string keySupportEntryValue;
    try
    {
        size_t keyEntryStart = deviceFileEntry.find( KEY_START_LINE ) + KEY_START_LINE.size();
        size_t keyEntryEnd = deviceFileEntry.find( '\n', keyEntryStart );

        if ( keyEntryStart == std::string::npos || keyEntryEnd == std::string::npos )
            return false;

        keySupportEntryValue = deviceFileEntry.substr( keyEntryStart, keyEntryEnd - keyEntryStart );
    }
    catch ( const std::out_of_range& e )
    {
        // TODO::ARGYRASPIDES() { Must replace with logging class in future }
        std::cerr << "PeripheralInfo::IsKeyboard() - " << e.what();
        return false;
    }

    std::stringstream ss( keySupportEntryValue );
    ss >> std::hex;

    uint64_t val;
    while ( ss >> val )
        ;

    int keyThreshold = 40;                   // The smallest practical keyboards have about 40 keys
    for ( int i = KEY_ESC; i < KEY_F6; i++ ) // Keys 1-63 cover most keyboards
    {
        if ( ( 1 << i ) & val )
            --keyThreshold;
    }

    return keyThreshold <= 0;
}

bool IsMouse( const std::string& deviceFileEntry ) noexcept
{
    if ( deviceFileEntry.empty() )
        return false;

    std::string handlersEntryValues;
    try
    {
        size_t handlersEntryStart = deviceFileEntry.find( HANDLERS_START_LINE ) + HANDLERS_START_LINE.size();
        size_t handlersEntryEnd = deviceFileEntry.find( '\n', handlersEntryStart );

        if ( handlersEntryStart == std::string::npos || handlersEntryEnd == std::string::npos )
            return false;

        handlersEntryValues = deviceFileEntry.substr( handlersEntryStart, handlersEntryEnd - handlersEntryStart );

        // E.g., H: Handlers=mouse2 event17 (we want to extract the event*, but make sure its a mouse by checking mouse
        // string before)
        size_t mouseEntryStartPos = handlersEntryValues.find( MOUSE_HANDLERS_ENTRY );

        if ( mouseEntryStartPos == std::string::npos )
            return false;

        return true;
    }
    catch ( const std::out_of_range& e )
    {
        // TODO::ARGYRASPIDES() { Must replace with logging class in future }
        std::cerr << "PeripheralInfo::IsKeyboard() - " << e.what();
        return false;
    }
}

std::optional< std::string > GetDeviceName( const std::string& deviceFileEntry ) noexcept
{
    if ( deviceFileEntry.empty() )
        return std::nullopt;

    std::string nameEntryValue;
    try
    {
        const size_t nameEntryStart = deviceFileEntry.find( NAME_START_LINE ) + NAME_START_LINE.size();
        const size_t nameEntryEnd = deviceFileEntry.find( '\n', nameEntryStart );

        if ( nameEntryStart == std::string::npos || nameEntryEnd == std::string::npos )
        {
            return std::nullopt;
        }

        nameEntryValue = deviceFileEntry.substr( nameEntryStart, nameEntryEnd - nameEntryStart );
    }
    catch ( const std::out_of_range& e )
    {
        // TODO::ARGYRASPIDES() { Must replace with logging class in future }
        std::cerr << "PeripheralInfo::GetDeviceName() - " << e.what();
        return std::nullopt;
    }

    return nameEntryValue.empty() ? std::nullopt : std::optional< std::string >( nameEntryValue );
}

std::optional< std::string > GetEventDeviceName( const std::string& deviceFileEntry ) noexcept
{
    if ( deviceFileEntry.empty() )
        return std::nullopt;

    std::string handlersEntryValue;
    try
    {
        const size_t handlersEntryStart = deviceFileEntry.find( HANDLERS_START_LINE ) + HANDLERS_START_LINE.size();
        const size_t handlersEntryEnd = deviceFileEntry.find( '\n', handlersEntryStart );

        if ( handlersEntryStart == std::string::npos || handlersEntryEnd == std::string::npos )
            return std::nullopt;

        handlersEntryValue = deviceFileEntry.substr( handlersEntryStart, handlersEntryEnd - handlersEntryStart );
    }
    catch ( const std::out_of_range& e )
    {
        // TODO::ARGYRASPIDES() { Must replace with logging class in future }
        std::cerr << "PeripheralInfo::GetHandlerNames() - " << e.what();
        return std::nullopt;
    }

    std::stringstream ss( handlersEntryValue );
    std::string handlerDeviceNames;

    std::string eventName;
    while ( ss >> eventName )
    {
        if ( eventName.find( EVENT_DEVICE_FILE_PREFIX_NAME ) != std::string::npos )
        {
            handlerDeviceNames = DEVICE_FILE_INTERFACE_PREFIX_PATH + "/" + eventName;
            break;
        }
    }

    return std::optional< std::string >{ handlerDeviceNames };
}

InputCommon::PeripheralHashSet GetConnectedPeripherals()
{
    if ( access( DEVICE_FILE_INFO_PATH.c_str(), F_OK ) != 0 )
        throw InputCommon::PeripheralInputException( "Something is seriously wrong! The file " + DEVICE_FILE_INFO_PATH +
                                                     " does not exist! What have you done to your Linux system???" );

    if ( access( DEVICE_FILE_INFO_PATH.c_str(), R_OK ) != 0 )
        throw InputCommon::PeripheralInputException(
            "Cannot open " + DEVICE_FILE_INFO_PATH +
            " to find connected keyboards. You must run this program with sudo!" );

    std::ifstream deviceFile( DEVICE_FILE_INFO_PATH );
    if ( !deviceFile.is_open() )
        throw InputCommon::PeripheralInputException(
            "Cannot open " + DEVICE_FILE_INFO_PATH +
            " to check for keyboards for an unknown reason! Something is very wrong!" );

    InputCommon::PeripheralHashSet connectedKeyboards;

    std::string currLine;
    std::stringstream ss;
    while ( std::getline( deviceFile, currLine, '\n' ) )
    {
        ss << currLine << "\n";

        if ( !currLine.empty() )
            continue;

        std::string completeDeviceEntry = ss.str();

        if ( !IsKeyboard( completeDeviceEntry ) && !IsMouse( completeDeviceEntry ) )
        {
            ss.str( "" );
            continue;
        }

        std::optional< std::string > deviceName = GetDeviceName( completeDeviceEntry );
        std::optional< std::string > eventDeviceName = GetEventDeviceName( completeDeviceEntry );

        if ( !deviceName.has_value() || !eventDeviceName.has_value() )
        {
            ss.str( "" );
            continue;
        }

        InputCommon::PeripheralInfo kbInfo{ deviceName.value(), eventDeviceName.value() };
        connectedKeyboards.insert( kbInfo );

        ss.str( "" );
    }

    return connectedKeyboards;
}

} // namespace InputPeripheralDetection