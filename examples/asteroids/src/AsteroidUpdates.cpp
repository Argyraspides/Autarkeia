#include "AsteroidUpdates.hpp"
#include "AsteroidUtils.hpp"
#include "DrawUtils.hpp"
#include "Game.hpp"
#include "GeoUtils.hpp"
#include <chrono>
#include <cmath>

void UpdateAsteroids( GameWorld& gameWorld, GameState& gameSettings, Frame& screen )
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

void UpdateBullets( GameWorld& gameWorld, GameState& gameSettings, Frame& screen )
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

void UpdateCollisions( GameWorld& gameWorld, GameState& gameSettings, Frame& screen )
{
    // Check if there is a collision between the ship and any of the asteroids.
    // If there is, asteroid disappears and ship loses health
    for ( Asteroid& asteroid : gameWorld.asteroids )
    {
        Sprite& ship = gameWorld.ship.GetSprite();
        const std::vector< Vec2I >& shipVertices = ship.GetPointCloud();
        const Vec2I shipPos = gameWorld.ship.GetPosition();

        for ( Vec2I shipVertex : shipVertices )
        {
            std::vector< Vec2I > asteroidVertices = asteroid.GetSprite().GetPointCloud();
            Vec2I asteroidPos = asteroid.GetPosition();
            for ( Vec2I& v : asteroidVertices )
                v = v + asteroidPos;

            // TODO::THINKABOUT::ARGYRASPIDES() { Might be worth making some event system? That way I can put all the
            // debug visualization logic there ... so idk dispatch an event or something with some callback or whatever or push to some event queue 
            // that is constantly being processed by another thread in the game }
            if ( GeoUtils::PointInPolygon( shipVertex + shipPos, asteroidVertices ) )
                DebugCollisionColors( ship.spriteColor, true );
            else
                DebugCollisionColors( ship.spriteColor, false );
        }
    }
}

#ifdef AUTARKEIA_DEBUG_ENABLED

void DebugCollisionColors( Color& color, bool collisionOccurred )
{
    if ( collisionOccurred )
    {
        color = Color::RED;
    }
    else
    {
        color = Color::WHITE;
    }
}

#endif