
#include "KeyboardInputHandler.hpp"
#include "Game.hpp"

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


void HandleInput( InputCommon::KeyboardInputHandler& kbd )
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
