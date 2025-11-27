#include "Characters.hpp"
#include "Game.hpp"
#include "TextDrawUtils.hpp"

void RenderBullets( GameWorld& gameWorld, Frame& screen )
{
    for ( Bullet& bullet : gameWorld.bullets )
        DrawUtils::DrawSprite( bullet.GetSprite(), screen, SHADE_4, bullet.GetPosition(), 0.0f, Frame::Section::TWO );
}

void RenderAsteroids( GameWorld& gameWorld, Frame& screen )
{
    for ( Asteroid& asteroid : gameWorld.asteroids )
    {
        DrawUtils::DrawSprite( asteroid.GetSprite(), screen, SHADE_4, asteroid.GetPosition(), 0.0f,
                               Frame::Section::TWO );
        DrawUtils::DrawPixel( asteroid.GetPosition(), screen, 'x', Frame::Section::TWO );
    }
}

void RenderShip( GameWorld& gameWorld, Frame& screen )
{
    DrawUtils::DrawSprite( gameWorld.ship.GetSprite(), screen, SHADE_4, gameWorld.ship.GetPosition(), 0.0f,
                           Frame::Section::TWO );
}

void RenderDebug( GameWorld& gameWorld, Frame& screen )
{
    DrawUtils::DrawText( std::to_string( gameWorld.collisions ), { 50, 25 }, screen, SHADE_4, 0.0f,
                         Frame::Section::ONE );
}