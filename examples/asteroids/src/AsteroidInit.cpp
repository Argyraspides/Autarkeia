#include "AsteroidInit.hpp"
#include "Game.hpp"

void InitializeGame( GameWorld& gameWorld, Frame& screen )
{
    gameWorld.ship.SetPosition( Vec2F( screen.Width() / 2, screen.Height() / 2 ) );
    screen.SetSection( Frame::Section::ONE, { 0, 0 }, { screen.Width(), 25 } );
    screen.SetSection( Frame::Section::TWO, { 0, 25 }, { screen.Width(), screen.Height() - 25 } );
}