#include "Characters.hpp"
#include "Game.hpp"

void RenderBullets( GameWorld& gameWorld, Frame& screen )
{
    for ( Bullet& bullet : gameWorld.bullets )
        DrawUtils::DrawSprite( bullet.GetSprite(), screen, SHADE_4, bullet.GetPosition() );
}

void RenderAsteroids( GameWorld& gameWorld, Frame& screen )
{
    for ( Asteroid& asteroid : gameWorld.asteroids )
    {
        DrawUtils::DrawSprite( asteroid.GetSprite(), screen, SHADE_4, asteroid.GetPosition() );
        DrawUtils::DrawPixel( asteroid.GetPosition(), screen, 'x' );
    }
}

void RenderShip( GameWorld& gameWorld, Frame& screen )
{
    DrawUtils::DrawSprite( gameWorld.ship.GetSprite(), screen, SHADE_4, gameWorld.ship.GetPosition() );
}