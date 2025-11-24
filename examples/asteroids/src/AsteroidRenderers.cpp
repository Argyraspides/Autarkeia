#include "Characters.hpp"
#include "Game.hpp"

void RenderBullets( GameWorld& gameWorld, Frame& screen )
{
    for ( Bullet& bullet : gameWorld.bullets )
        DrawUtils::DrawSpriteOnFrame( bullet.GetSprite(), screen, SHADE_4, bullet.GetPosition() );
}

void RenderAsteroids( GameWorld& gameWorld, Frame& screen )
{
    for ( Asteroid& asteroid : gameWorld.asteroids )
    {
        DrawUtils::DrawSpriteOnFrame( asteroid.GetSprite(), screen, SHADE_4, asteroid.GetPosition() );
        DrawUtils::DrawPixelOnFrame( asteroid.GetPosition(), screen, 'x' );
    }
}

void RenderShip( GameWorld& gameWorld, Frame& screen )
{
    DrawUtils::DrawSpriteOnFrame( gameWorld.ship.GetSprite(), screen, SHADE_4, gameWorld.ship.GetPosition() );
}