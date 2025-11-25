#include "AsteroidInit.hpp"
#include "Frame.hpp"
#include "Game.hpp"

void InitializeGame( GameWorld& gameWorld, Frame& screen )
{
    gameWorld.ship.SetPosition( Vec2F( screen.Width() / 2, screen.Height() / 2 ) );
}