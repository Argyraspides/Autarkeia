#pragma once
#include <array>

struct GameWorld;
class Frame;

void RenderBullets( GameWorld& gameWorld, Frame& screen );
void RenderAsteroids( GameWorld& gameWorld, Frame& screen );
void RenderShip( GameWorld& gameWorld, Frame& screen );

inline std::array< void ( * )( GameWorld& gameWorld, Frame& screen ), 3 > 
renderTable = 
{ 
    RenderBullets,
    RenderAsteroids, 
    RenderShip 
};