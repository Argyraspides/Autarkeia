#pragma once
#include <array>
struct GameWorld;
struct GameState;
struct Event;

namespace InputCommon
{
class PeripheralInputHandler;
}

void HandleInputs( GameWorld& , GameState& , InputCommon::PeripheralInputHandler& );
void HandleKeyboardInputs( GameWorld&, GameState&, Event );
void HandleMouseInputs( GameWorld&, GameState&, Event );

inline std::array< void ( * )( 
GameWorld& gameWorld, 
GameState& gameSettings, 
InputCommon::PeripheralInputHandler& kbd ), 1 >
inputTable = 
{ 
   HandleInputs
};