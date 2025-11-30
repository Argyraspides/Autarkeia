#include "AsteroidInputs.hpp"
#include "Game.hpp"
#include "PeripheralInputHandler.hpp"
#include <cmath>
#include <linux/input-event-codes.h>

void HandleInputs( GameWorld& gameWorld, GameState& gameSettings, InputCommon::PeripheralInputHandler& pih )
{
    Event userInput = pih.GetNextEvent();

    switch ( userInput.eventType )
    {
    case EventType::KEYBOARD_PRESS:
    case EventType::KEYBOARD_HELD:
        HandleKeyboardInputs( gameWorld, gameSettings, userInput );
        break;
    case EventType::TOUCHPAD_MOVEMENT:
    case EventType::TOUCHPAD_ABSOLUTE_X_POS:
    case EventType::TOUCHPAD_ABSOLUTE_Y_POS:
        HandleMouseInputs( gameWorld, gameSettings, userInput );
        break;
    default:;
    }
}

void HandleKeyboardInputs( GameWorld& gameWorld, GameState& gameSettings, Event userInput )
{
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

    switch ( userInput.eventValue )
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
    case KEY_GRAVE:
        gameSettings.tickForward = true;
    }
}

void HandleMouseInputs( GameWorld& gameWorld, GameState& gameSettings, Event userInput )
{
    switch ( userInput.eventType )
    {
    case EventType::TOUCHPAD_ABSOLUTE_X_POS:
        gameSettings.mousePos.x = userInput.eventValue;
    case EventType::TOUCHPAD_ABSOLUTE_Y_POS:
        gameSettings.mousePos.y = userInput.eventValue;
    default:;
    }
}