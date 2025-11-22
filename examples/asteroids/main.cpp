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
long asteroidGenerationPeriodMs = 5000;

InputCommon::KeyboardInputHandler kbd;

std::list< Bullet > bullets;
std::list< Asteroid > asteroids;

Ship ship;

int rotationSpeed = 5;

bool paused = false;

void RenderBullets()
{
    for ( Bullet& bullet : bullets )
        DrawUtils::DrawSpriteOnFrame( bullet.GetSprite(), screen, SHADE_4, bullet.GetPosition() );
}

void RenderAsteroids()
{
    for ( Asteroid& asteroid : asteroids )
    {
        DrawUtils::DrawSpriteOnFrame( asteroid.GetSprite(), screen, SHADE_4, asteroid.GetPosition() );
        DrawUtils::DrawPixelOnFrame( asteroid.GetPosition(), screen, 'x' );
    }
}

void RenderShip()
{
    DrawUtils::DrawSpriteOnFrame( ship.GetSprite(), screen, SHADE_4, ship.GetPosition() );
    auto v = ship.GetSprite().GetPointCloud();
    for ( auto vec : v )
    {
        DrawUtils::DrawPixelOnFrame( vec + ship.GetPosition(), screen, 'V' );
    }
    DrawUtils::DrawPixelOnFrame( ship.GetPosition(), screen, 'C' );
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
        int newRotation = ( ship.GetRotation() + ( rotationSpeed * direction ) ) % 360;
        ship.Rotate( newRotation );
    };

    auto SpawnBullet = []() {
        Bullet newBullet = Bullet{};
        newBullet.SetPosition( ship.GetPosition() );
        int shipRotation = ship.GetRotation();
        float shipRotationRad = static_cast< float >( shipRotation ) * ( M_PI / 180.0f );
        Vec2F bulletVelocity = { std::cos( shipRotationRad ), std::sin( shipRotationRad ) };
        newBullet.SetVelocity( bulletVelocity );
        bullets.push_back( newBullet );
    };

    auto MoveShip = []() {
        float heading = ( M_PI / 180.0F ) * ship.GetRotation();
        Vec2F shipDir = { std::cos( heading ), std::sin( heading ) };
        ship.Move( shipDir );
    };

    switch ( userInput.value() )
    {
    case KEY_LEFT:
        RotateShip( 1 );
        break;
    case KEY_RIGHT:
        RotateShip( -1 );
        break;
    case KEY_P:
        paused = !paused;
        break;
    case KEY_RIGHTALT:
    case KEY_LEFTALT:
        MoveShip();
        break;
    case KEY_SPACE:
        SpawnBullet();
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

void MakeRandomAsteroid()
{
    static const long framesForOneAsteroid = asteroidGenerationPeriodMs / frameTimeMs;
    static long elapsedFrames = 0;

    static auto anchorTime = std::chrono::system_clock::now();
    auto now = std::chrono::system_clock::now();

    auto elapsed = std::chrono::duration_cast< std::chrono::milliseconds >( now - anchorTime );

    if ( ( now - anchorTime ).count() >= frameTimeMs )
    {
        ++elapsedFrames;
        anchorTime = std::chrono::system_clock::now();
    }

    if ( elapsedFrames == framesForOneAsteroid )
    {
        elapsedFrames = 0;
        Asteroid asteroid{ static_cast< size_t >( ( rand() % 10 ) + 3 ) };
        Frame::Border randomBorder = static_cast< Frame::Border >( rand() % static_cast< int >( Frame::Border::MAX ) );

        Vec2F asteroidSpawnPos;
        switch ( randomBorder )
        {
        case Frame::Border::TOP:
            asteroidSpawnPos = Vec2F( rand() % screen.Width(), 0 );
            break;
        case Frame::Border::BOTTOM:
            asteroidSpawnPos = Vec2F( rand() % screen.Width(), screen.Height() - 1 );
            break;
        case Frame::Border::LEFT:
            asteroidSpawnPos = Vec2F( 1, rand() % screen.Height() );
            break;
        case Frame::Border::RIGHT:
            asteroidSpawnPos = Vec2F( screen.Width() - 1, rand() % screen.Height() );
            break;
        default:;
        }

        asteroid.SetPosition( asteroidSpawnPos );

        Vec2F screenCenter = Vec2F( screen.Width() / 2, screen.Height() / 2 );
        Vec2F centerVec = screenCenter - asteroid.GetPosition();

        asteroid.SetVelocity( centerVec.Normalized() * 5 );
        asteroids.push_back( asteroid );
    }
}

void UpdateAsteroids()
{
    MakeRandomAsteroid();

    for ( auto asteroid = asteroids.begin(); asteroid != asteroids.end(); )
    {
        if ( !screen.InFrame( ( *asteroid ).GetPosition() ) )
        {
            asteroid = asteroids.erase( asteroid );
            continue;
        }

        ( *asteroid ).Move( ( *asteroid ).GetVelocity() );
        ++asteroid;
    }
}

void UpdateLoop()
{
    HandleInput();
    UpdateBullets();
    UpdateAsteroids();
}

int main()
{
    DrawUtils::SetToSystemLocale();
    kbd.Start();
    ship.SetPosition( Vec2F( screen.Width() / 2, screen.Height() / 2 ) );

    while ( true )
    {
        std::this_thread::sleep_for( std::chrono::milliseconds( frameTimeMs ) );

        if ( paused )
            continue;

        UpdateLoop();
        RenderLoop();
    }
}