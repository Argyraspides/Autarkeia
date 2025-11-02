#include "DrawUtils.hpp"
#include "Frame.hpp"
#include "ShipSprite.hpp"
#include <chrono>
#include <thread>

Frame screen( 35, 35 );
float frameTimeMs = 2000;

int main()
{
    Sprite sprite( 25, 25 );
    DrawUtils::ClearFrame( sprite.frame, ' ' );

    Vec2I p1 = { sprite.frame.Width() / 2, 0 };
    Vec2I p2 = { 1, sprite.frame.Height() - 1 };
    Vec2I p3 = { sprite.frame.Width() - 2, sprite.frame.Height() - 1 };

    DrawUtils::QuickDrawTriangle( p1, p2, p3, sprite.frame, '.' );
    DrawUtils::QuickDrawLine(p1, (p1 + p2 + p3) / 3, sprite.frame, 'l');

    std::chrono::time_point< std::chrono::steady_clock, std::chrono::nanoseconds > lastFrameTime =
        std::chrono::steady_clock::now();

    while ( true )
    {
        std::chrono::time_point< std::chrono::steady_clock, std::chrono::nanoseconds > endFrameTime =
            lastFrameTime + std::chrono::milliseconds( static_cast< int >( frameTimeMs ) );

        std::this_thread::sleep_for( std::chrono::milliseconds( static_cast< int >( frameTimeMs - 1 ) ) );

        while ( std::chrono::steady_clock::now() < endFrameTime )
            ;
        lastFrameTime = std::chrono::steady_clock::now();

        DrawUtils::ClearFrame( screen, ' ' );
        DrawUtils::RotateSprite( sprite, 45);
        DrawUtils::DrawSpriteOnFrame( sprite, screen, { 10, 10 } );
        DrawUtils::DrawFrame( screen );
        DrawUtils::ResetTerminalCursor();
    }
}