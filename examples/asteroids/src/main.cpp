#include "Characters.hpp"
#include "DrawUtils.hpp"
#include "Frame.hpp"
#include "ShipSprite.hpp"
#include "SpritePC.hpp"
#include <chrono>
#include <thread>

Frame screen( 500, 200 );
// Sprite triangle( 20, 20);
SpritePC triangle;

int main()
{
    DrawUtils::SetToSystemLocale();

    int sideOffset = 10;
    int triWidth = 50;
    int triHeight = 50;

    // Vec2I p1 = { triangle.GetFrameC().Width() / 2, sideOffset };
    // Vec2I p2 = { sideOffset, triangle.GetFrameC().Height() - sideOffset };
    // Vec2I p3 = { triangle.GetFrameC().Width() - sideOffset, triangle.GetFrameC().Height() - sideOffset };

    Vec2I p1 = { triWidth / 2, sideOffset };
    Vec2I p2 = { sideOffset, triHeight - sideOffset };
    Vec2I p3 = { triWidth - sideOffset, triHeight - sideOffset };

    triangle.points = ( std::vector< Vec2I >{ p1, p2, p3 } );
    DrawUtils::DrawTriangleOnFrame( p1, p2, p3, screen, SHADE_4 );

    int rotation = 0;
    while ( true )
    {
        DrawUtils::ResetTerminalCursor();
        DrawUtils::ClearFrame( screen, SHADE_0 );
        DrawUtils::DrawBorderOnFrame( screen );

        rotation = ( rotation + 10 ) % 360;
        DrawUtils::RotateSprite( triangle, rotation );

        for ( int i = 0; i < triangle.rotatedPoints.size(); i++ )
        {
            DrawUtils::DrawLineOnFrame( triangle.rotatedPoints[ i ],
                                        triangle.rotatedPoints[ ( i + 1 ) % triangle.rotatedPoints.size() ], screen,
                                        SHADE_4 );
        }

        // DrawUtils::DrawSpriteOnFrame( triangle, screen, { 50, 50 }, rotation );
        DrawUtils::DrawFrame( screen );

        std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );
    }
}