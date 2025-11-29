#include "Characters.hpp"
#include "DrawUtils.hpp"
#include "Game.hpp"
#include "Ship.hpp"
#include "TextDrawUtils.hpp"

void RenderBullets( GameWorld& gameWorld, Frame& screen )
{
    for ( Bullet& bullet : gameWorld.bullets )
    {
        Color spriteColor = bullet.GetSprite().spriteColor;
        DrawUtils::DrawSprite( bullet.GetSprite(), screen, { SHADE_4, spriteColor }, bullet.GetPosition(),
                               Frame::Section::TWO );
    }
}

void RenderAsteroids( GameWorld& gameWorld, Frame& screen )
{
    for ( Asteroid& asteroid : gameWorld.asteroids )
    {
        Color spriteColor = asteroid.GetSprite().spriteColor;
        DrawUtils::DrawSprite( asteroid.GetSprite(), screen, { SHADE_4, spriteColor }, asteroid.GetPosition(),
                               Frame::Section::TWO );
    }
}

void RenderShip( GameWorld& gameWorld, Frame& screen )
{
    Color spriteColor = gameWorld.ship.GetSprite().spriteColor;
    DrawUtils::DrawSprite( gameWorld.ship.GetSprite(), screen, { SHADE_4, spriteColor }, gameWorld.ship.GetPosition(),
                           Frame::Section::TWO );
}

void RenderDebug( GameWorld& gameWorld, Frame& screen )
{
    DrawUtils::DrawText( std::to_string( gameWorld.collisions ), { 50, 25 }, screen, SHADE_4, 0.0f,
                         Frame::Section::ONE );
}