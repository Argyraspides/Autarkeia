#include "Game.hpp"
#include <cmath>
#include <linux/input-event-codes.h>

void HandleInput( GameWorld& gameWorld, GameSettings& gameSettings, InputCommon::KeyboardInputHandler& kbd )
{
    std::optional< InputCommon::KeyInputCode > userInput = kbd.GetNextKeyPress();
    if ( !userInput )
        return;

    auto RotateShip = [ &gameWorld, &gameSettings ]( int direction ) {
        int newRotation = ( gameWorld.ship.GetRotation() + ( gameSettings.shipRotSpeed * direction ) ) % 360;
        gameWorld.ship.Rotate( newRotation );
    };

    auto SpawnBullet = [ &gameWorld ]() {
        Bullet newBullet = Bullet{};
        newBullet.SetPosition( gameWorld.ship.GetPosition() );
        int shipRotation = gameWorld.ship.GetRotation();
        float shipRotationRad = static_cast< float >( shipRotation ) * ( M_PI / 180.0f );
        Vec2F bulletVelocity = { std::cos( shipRotationRad ), std::sin( shipRotationRad ) };
        newBullet.SetVelocity( bulletVelocity );
        gameWorld.bullets.push_back( newBullet );
    };

    auto MoveShip = [ &gameWorld ]() {
        float heading = ( M_PI / 180.0F ) * gameWorld.ship.GetRotation();
        Vec2F shipDir = { std::cos( heading ), std::sin( heading ) };
        gameWorld.ship.Move( shipDir );
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
        gameSettings.gamePaused = !gameSettings.gamePaused;
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