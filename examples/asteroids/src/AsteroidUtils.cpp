#include "AsteroidUtils.hpp"
#include "Asteroid.hpp"
#include "Frame.hpp"

Asteroid MakeRandomAsteroid( Frame& screen )
{
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

    return asteroid;
}