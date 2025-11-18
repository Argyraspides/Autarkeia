#include "Asteroid.hpp"
#include "Bullet.hpp"
#include "Ship.hpp"

#include "Characters.hpp"
#include "DrawUtils.hpp"
#include "Frame.hpp"
#include "KeyboardInputHandler.hpp"
#include "Vec2I.hpp"

#include <chrono>
#include <cmath>
#include <linux/input-event-codes.h>
#include <list>
#include <optional>
#include <thread>

Frame screen( 500, 200 );
long frameTimeMs = 16;

InputCommon::KeyboardInputHandler kbd;

std::list< Bullet > bullets;
std::list< Asteroid > asteroids;

Ship ship;

int rotationSpeed = 10;

void RenderBullets()
{
    for ( Bullet& bullet : bullets )
        DrawUtils::DrawSpriteOnFrame( bullet.GetSprite(), screen, SHADE_4, bullet.GetPosition() );
}

void RenderAsteroids()
{
    for ( Asteroid& asteroid: asteroids )
        DrawUtils::DrawSpriteOnFrame( asteroid.GetSprite(), screen, SHADE_4, asteroid.GetPosition() );
}

void RenderShip()
{
    DrawUtils::DrawSpriteOnFrame( ship.GetSprite(), screen, SHADE_4, ship.GetPosition() );
}

void RenderLoop()
{
    DrawUtils::ClearFrame( screen, SHADE_0 );
    DrawUtils::DrawBorderOnFrame( screen );

    RenderBullets();
    RenderAsteroids();
    RenderShip();

    DrawUtils::ResetTerminalCursor();
    DrawUtils::DrawFrame( screen );
}

void HandleInput()
{
    std::optional< InputCommon::KeyInputCode > userInput = kbd.GetNextKeyPress();
    if ( !userInput )
        return;

    auto RotateShip = []( int direction ) {
        static int currentRotation = 0;
        currentRotation = ( currentRotation + ( rotationSpeed * direction ) ) % 360;
        ship.Rotate( currentRotation );
    };

    switch ( userInput.value() )
    {
    case KEY_LEFT:
        RotateShip( 1 );
        break;
    case KEY_RIGHT:
        RotateShip( -1 );
        break;
    case KEY_W:
        ship.Move( VEC2F_UP );
        break;
    case KEY_A:
        ship.Move( VEC2F_LEFT );
        break;
    case KEY_S:
        ship.Move( VEC2F_DOWN );
        break;
    case KEY_D:
        ship.Move( VEC2F_RIGHT );
        break;
    case KEY_E:
        ship.Move( VEC2F_RIGHT );
        ship.Move( VEC2F_UP );
        break;
    case KEY_Q:
        ship.Move( VEC2F_LEFT );
        ship.Move( VEC2F_UP );
        break;
    case KEY_C:
        ship.Move( VEC2F_RIGHT );
        ship.Move( VEC2F_DOWN );
        break;
    case KEY_LEFTSHIFT:
        ship.Move( VEC2F_LEFT );
        ship.Move( VEC2F_DOWN );
        break;
    case KEY_SPACE:
        Bullet newBullet = Bullet{};
        newBullet.SetPosition( ship.GetPosition() + ship.GetSprite().GetCentroidModified() );
        int shipRotation = ship.GetRotation();
        float shipRotationRad = static_cast< float >( shipRotation ) * ( M_PI / 180.0f );
        Vec2F bulletVelocity = { std::cos( shipRotationRad ), std::sin( shipRotationRad ) };
        newBullet.SetVelocity( bulletVelocity );
        bullets.push_back( newBullet );
        break;
    }
}

void UpdateBullets()
{
    for ( auto it = bullets.begin(); it != bullets.end(); )
    {
        Bullet& bullet = *it;

        bullet.Move( bullet.GetVelocity() );

        Vec2I bulletPos = bullet.GetPosition();
        if ( !screen.InFrame( bulletPos ) )
            it = bullets.erase( it );
        else
            ++it;
    }
}
void UpdateLoop()
{
    HandleInput();
    UpdateBullets();
}

int main()
{
    DrawUtils::SetToSystemLocale();
    kbd.Start();
    ship.SetPosition( Vec2F( screen.Width() / 2, screen.Height() / 2 ) );

    Asteroid a;
    a.SetPosition( { 50, 50 } );
    asteroids.push_back( a );

    auto lastFrameTime = std::chrono::steady_clock::now();
    // while ( true )
    {
        // std::this_thread::sleep_for( std::chrono::milliseconds( frameTimeMs ) );
        UpdateLoop();
        RenderLoop();
    }
}