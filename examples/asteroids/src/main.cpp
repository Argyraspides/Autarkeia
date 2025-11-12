#include "Characters.hpp"
#include "DrawUtils.hpp"
#include "Frame.hpp"
#include "KeyboardInputHandler.hpp"
#include "Ship.hpp"
#include "Vec2I.hpp"

#include <chrono>
#include <linux/input-event-codes.h>
#include <optional>
#include <thread>

Frame screen( 500, 200 );
long frameTimeMs = 16;

InputCommon::KeyboardInputHandler kbd;

std::vector< Entity > bullets;
Ship ship;
int rotationSpeed = 10;

void RenderLoop()
{
    DrawUtils::ClearFrame( screen, SHADE_0 );
    DrawUtils::DrawBorderOnFrame( screen );

    DrawUtils::DrawSpriteOnFrame( ship.GetSprite(), screen, SHADE_4, ship.GetPosition() );

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
        ship.Move( VEC2I_UP );
        break;
    case KEY_A:
        ship.Move( VEC2I_LEFT );
        break;
    case KEY_S:
        ship.Move( VEC2I_DOWN );
        break;
    case KEY_D:
        ship.Move( VEC2I_RIGHT );
        break;
    case KEY_E:
        ship.Move( VEC2I_RIGHT );
        ship.Move( VEC2I_UP );
        break;
    case KEY_Q:
        ship.Move( VEC2I_LEFT );
        ship.Move( VEC2I_UP );
        break;
    case KEY_C:
        ship.Move( VEC2I_RIGHT );
        ship.Move( VEC2I_DOWN );
        break;
    case KEY_LEFTSHIFT:
        ship.Move( VEC2I_LEFT );
        ship.Move( VEC2I_DOWN );
        break;
    }
}

void UpdateBullets()
{
}

void UpdateLoop()
{
    HandleInput();
}

int main()
{
    DrawUtils::SetToSystemLocale();
    kbd.Start();
    ship.Move( { screen.Width() / 2, screen.Height() / 2 });

    auto lastFrameTime = std::chrono::steady_clock::now();
    int rotation = 0;
    while ( true )
    {
        std::this_thread::sleep_for( std::chrono::milliseconds( frameTimeMs ) );
        UpdateLoop();
        RenderLoop();
    }
}