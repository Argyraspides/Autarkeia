#pragma once
#include <array>

struct GameWorld;
class Frame;

void RenderBullets( GameWorld& gameWorld, Frame& screen );
void RenderAsteroids( GameWorld& gameWorld, Frame& screen );
void RenderShip( GameWorld& gameWorld, Frame& screen );
void RenderDebug( GameWorld& gameWorld, Frame& screen );

inline std::array< void ( * )( GameWorld& gameWorld, Frame& screen ), 4 > 
renderTable = 
{ 
    RenderBullets,
    RenderAsteroids, 
    RenderShip, 
    RenderDebug 
};