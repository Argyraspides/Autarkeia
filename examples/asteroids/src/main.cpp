#include "Characters.hpp"
#include "DrawUtils.hpp"
#include "Frame.hpp"
#include "ShipSprite.hpp"
#include <chrono>
#include <thread>

Frame screen( 500, 200);
Sprite triangle( 150, 150);

int main()
{
    DrawUtils::SetToSystemLocale();

    int sideOffset = triangle.GetFrameC().Width() / 5;

    Vec2I p1 = { triangle.GetFrameC().Width() / 2, sideOffset };
    Vec2I p2 = { sideOffset, triangle.GetFrameC().Height() - sideOffset };
    Vec2I p3 = { triangle.GetFrameC().Width() - sideOffset, triangle.GetFrameC().Height() - sideOffset };
    DrawUtils::DrawTriangleOnFrame( p1, p2, p3, triangle.GetFrame(), SHADE_4 );

    int rotation = 0;
    while ( true )
    {
        DrawUtils::ResetTerminalCursor();
        DrawUtils::ClearFrame( screen, SHADE_0 );
        DrawUtils::DrawBorderOnFrame( screen );

        rotation = ( rotation + 10 ) % 360;
        DrawUtils::DrawSpriteOnFrame( triangle, screen, { 10, 10 }, rotation );
        DrawUtils::DrawFrame( screen );

        std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );
    }
}