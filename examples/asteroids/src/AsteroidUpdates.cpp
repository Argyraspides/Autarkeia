#include "AsteroidUtils.hpp"
#include "Game.hpp"
#include <cmath>

void UpdateAsteroids( GameWorld& gameWorld, Frame& screen )
{
    Asteroid asteroid = MakeRandomAsteroid( screen ); 
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

void UpdateBullets( GameWorld& gameWorld, Frame& screen )
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
