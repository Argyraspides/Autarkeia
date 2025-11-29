//
// Created by gaugamela on 9/11/25.
//
#pragma once

#include <string>
#include <unordered_set>
#include <utility>

namespace InputCommon
{
struct PeripheralInfo
{
    std::string peripheralName;
    std::string eventDevicePath;

    PeripheralInfo( std::string keyboardName, std::string eventDevicePath )
        : peripheralName( std::move( keyboardName ) ),
          eventDevicePath( std::move( eventDevicePath ) )
    {
    }
};

struct PeripheralInfoHashFunc
{
    std::size_t operator()( const PeripheralInfo& k1 ) const
    {
        std::hash< std::string > stringHash;
        return stringHash( k1.eventDevicePath );
    }
};

struct PeripheralInfoEqualFunc
{
    bool operator()( const PeripheralInfo& k1, const PeripheralInfo& k2 ) const
    {
        return k1.eventDevicePath == k2.eventDevicePath;
    }
};

using PeripheralHashSet = std::unordered_set< PeripheralInfo, PeripheralInfoHashFunc, PeripheralInfoEqualFunc >;

} // namespace InputCommon
