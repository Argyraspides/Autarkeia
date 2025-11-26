#include "AsteroidUtils.hpp"
#include "Game.hpp"
#include <chrono>
#include <cmath>

void UpdateAsteroids( GameWorld& gameWorld, GameSettings& gameSettings, Frame& screen )
{
    static auto anchorTime = std::chrono::system_clock::now();
    auto now = std::chrono::system_clock::now();

    auto timeSinceLastUpdateMs = std::chrono::duration_cast< std::chrono::milliseconds >( now - anchorTime );
    if ( timeSinceLastUpdateMs.count() >= gameSettings.asteroidGenerationPeriodMs )
    {
        Asteroid asteroid = MakeRandomAsteroid( screen );
        gameWorld.asteroids.push_back( asteroid );
        anchorTime = std::chrono::system_clock::now();
    }

    for ( auto asteroid = gameWorld.asteroids.begin(); asteroid != gameWorld.asteroids.end(); )
    {
        if ( !screen.InFrame( ( *asteroid ).GetPosition() ) )
        {
            asteroid = gameWorld.asteroids.erase( asteroid );
            continue;
        }

        ( *asteroid ).Move( ( *asteroid ).GetVelocity() );
        ++asteroid;
    }
}

void UpdateBullets( GameWorld& gameWorld, GameSettings& gameSettings, Frame& screen )
{
    for ( auto it = gameWorld.bullets.begin(); it != gameWorld.bullets.end(); )
    {
        Bullet& bullet = *it;

        bullet.Move( bullet.GetVelocity() );

        Vec2I bulletPos = bullet.GetPosition();
        if ( !screen.InFrame( bulletPos ) )
            it = gameWorld.bullets.erase( it );
        else
            ++it;
    }
}

void UpdateCollisions( GameWorld& gameWorld, GameSettings& gameSettings, Frame& screen )
{
    // Check if there is a collision between the ship and any of the asteroids.
    // If there is, asteroid disappears and ship loses health
}