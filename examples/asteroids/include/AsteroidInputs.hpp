#pragma once
#include <array>
struct GameWorld;
struct GameSettings;

namespace InputCommon
{
class PeripheralInputHandler;
}

void HandleInput( GameWorld& gameWorld, GameSettings& gameSettings, InputCommon::PeripheralInputHandler& kbd );

inline std::array< void ( * )( 
GameWorld& gameWorld, 
GameSettings& gameSettings, 
InputCommon::PeripheralInputHandler& kbd ), 1 >
inputTable = 
{ 
    HandleInput 
};