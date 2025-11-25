#pragma once
#include <array>
struct GameWorld;
struct GameSettings;

namespace InputCommon
{
class KeyboardInputHandler;
}

void HandleInput( GameWorld& gameWorld, GameSettings& gameSettings, InputCommon::KeyboardInputHandler& kbd );

inline std::array< void ( * )( 
GameWorld& gameWorld, 
GameSettings& gameSettings, 
InputCommon::KeyboardInputHandler& kbd ), 1 >
inputTable = 
{ 
    HandleInput 
};