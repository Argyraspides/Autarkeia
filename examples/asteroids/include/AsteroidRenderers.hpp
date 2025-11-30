#pragma once
#include <array>

struct GameWorld;
struct GameState;
class Frame;

void RenderBullets( GameWorld& gameWorld, GameState& gameSettings, Frame& screen );
void RenderAsteroids( GameWorld& gameWorld, GameState& gameSettings, Frame& screen );
void RenderShip( GameWorld& gameWorld, GameState& gameSettings, Frame& screen );
void RenderDebug( GameWorld& gameWorld, GameState& gameSettings, Frame& screen );

inline std::array< void ( * )( GameWorld& gameWorld, GameState& gameSettings, Frame& screen ), 4 > 
renderTable = 
{ 
    RenderBullets,
    RenderAsteroids, 
    RenderShip, 
    RenderDebug 
};