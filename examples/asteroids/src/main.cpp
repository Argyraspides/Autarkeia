#include "Characters.hpp"
#include "DrawUtils.hpp"
#include "Frame.hpp"
#include "KeyboardInputHandler.hpp"
#include "ShipSprite.hpp"

#include <chrono>
#include <linux/input-event-codes.h>
#include <optional>
#include <thread>

// Max size I can fit on a 1080p display max zoom
Frame screen( 500, 140 );
long frameTimeMs = 16;

InputCommon::KeyboardInputHandler kbd;

std::vector< Sprite > bullets;

void Render()
{
    DrawUtils::ClearFrame( screen, SHADE_0 );

    DrawUtils::DrawSpriteOnFrame( spaceShip, screen, 'x', { 50, 50 } );

    DrawUtils::ResetTerminalCursor();
    DrawUtils::DrawFrame( screen );
}

void HandleShoot()
{
    std::optional< InputCommon::KeyInputCode > userInput = kbd.GetNextKeyPress();
    if ( !userInput )
        return;

    if ( userInput.value() != KEY_SPACE )
        return;

    bullets.push_back( Sprite{ spaceShip } );
}

void UpdateBullets()
{
    // for( Sprite& )
}

void Update()
{
    HandleShoot();
}

int main()
{
    DrawUtils::SetToSystemLocale();
    kbd.Start();

    auto lastFrameTime = std::chrono::steady_clock::now();
    int rotation = 0;
    while ( true )
    {
        std::this_thread::sleep_for( std::chrono::milliseconds( frameTimeMs ) );
        Update();
        Render();
    }
}