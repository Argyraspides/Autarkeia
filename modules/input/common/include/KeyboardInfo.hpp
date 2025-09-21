//
// Created by gaugamela on 9/11/25.
//

#ifndef AUTARKEIA_KEYBOARDINFO_HPP
#define AUTARKEIA_KEYBOARDINFO_HPP
#include <string>
#include <utility>
#include <unordered_set>

namespace InputCommon
{
struct KeyboardInfo
{
    std::string keyboardName;
    std::string eventDevicePath;

    KeyboardInfo( std::string keyboardName, std::string eventDevicePath )
        : keyboardName( std::move( keyboardName ) ),
          eventDevicePath( std::move( eventDevicePath ) )
    {
    }
};

struct KeyboardInfoHashFunc
{
    std::size_t operator()(const KeyboardInfo& k1 ) const
    {
        std::hash< std::string > stringHash;
        return stringHash(k1.eventDevicePath);
    }
};

struct KeyboardInfoEqualFunc
{
    bool operator()(const KeyboardInfo& k1, const KeyboardInfo& k2 ) const
    {
        return k1.eventDevicePath == k2.eventDevicePath;
    }
};

using KeyboardHashSet = std::unordered_set< KeyboardInfo, KeyboardInfoHashFunc, KeyboardInfoEqualFunc >;

} // namespace InputCommon

#endif // AUTARKEIA_KEYBOARDINFO_HPP
