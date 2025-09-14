//
// Created by gaugamela on 9/11/25.
//
#include "InputPeripheralDetection.hpp"
#include "PeripheralInputException.hpp"
#include <iostream>
#include <linux/input-event-codes.h>
#include <sstream>
#include <unistd.h>

static inline std::string EV_START_LINE = "B: EV=";
static inline std::string KEY_START_LINE = "B: KEY=";
static inline std::string NAME_START_LINE = "N: Name=";
static inline std::string HANDLERS_START_LINE = "H: Handlers=";

static inline std::string DEVICE_FILE_INFO_PATH = "/proc/bus/input/devices";
static inline std::string DEVICE_FILE_INTERFACE_PREFIX_PATH = "/dev/input";

static inline std::string EVENT_DEVICE_FILE_PREFIX_NAME = "event";

namespace InputPeripheralDetection
{
bool IsKeyboard( const std::string& deviceFileEntry )
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
        std::cerr << "KeyboardInfo::IsKeyboard() - " << e.what();
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

std::optional< std::string > GetDeviceName( const std::string& deviceFileEntry )
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
        std::cerr << "KeyboardInfo::GetDeviceName() - " << e.what();
        return std::nullopt;
    }

    return nameEntryValue.empty() ? std::nullopt : std::optional< std::string >( nameEntryValue );
}

std::optional< std::string > GetEventDeviceName( const std::string& deviceFileEntry )
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
        std::cerr << "KeyboardInfo::GetHandlerNames() - " << e.what();
        return std::nullopt;
    }

    std::stringstream ss( handlersEntryValue );
    std::string handlerDeviceNames;

    std::string eventName;
    while ( ss >> eventName )
    {
        if ( eventName.find( EVENT_DEVICE_FILE_PREFIX_NAME ) != std::string::npos )
        {
            // TODO::ARGYRASPIDES() { Find out if there might actually be multiple 'event' files per device??? }
            handlerDeviceNames = DEVICE_FILE_INTERFACE_PREFIX_PATH.append( "/" ).append( eventName );
            break;
        }
    }

    return std::optional< std::string >{ handlerDeviceNames };
}

std::vector< InputCommon::KeyboardInfo > GetConnectedKeyboards()
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

    std::vector< InputCommon::KeyboardInfo > connectedKeyboards;

    std::string currLine;
    std::stringstream ss;
    while ( std::getline( deviceFile, currLine, '\n' ) )
    {
        ss << currLine << "\n";

        if ( !currLine.empty() )
            continue;

        std::string completeDeviceEntry = ss.str();
        if ( !IsKeyboard( completeDeviceEntry ) )
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

        InputCommon::KeyboardInfo kbInfo{ deviceName.value(), eventDeviceName.value() };
        connectedKeyboards.push_back( kbInfo );

        ss.str( "" );
    }

    return connectedKeyboards;
}

} // namespace InputPeripheralDetection