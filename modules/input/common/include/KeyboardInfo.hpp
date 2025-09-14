//
// Created by gaugamela on 9/11/25.
//

#ifndef AUTARKEIA_KEYBOARDINFO_HPP
#define AUTARKEIA_KEYBOARDINFO_HPP
#include <string>
#include <utility>

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
} // namespace InputCommon

#endif // AUTARKEIA_KEYBOARDINFO_HPP
