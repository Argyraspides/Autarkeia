#include "Characters.hpp"
#include "DrawUtils.hpp"
#include "Frame.hpp"
#include "Sprite.hpp"
#include <chrono>
#include <thread>

Frame screen( 500, 200 );
int sideOffset = 10;
int triWidth = 50;
int triHeight = 50;

Vec2I p1 = { triWidth / 2, sideOffset };
Vec2I p2 = { sideOffset, triHeight - sideOffset };
Vec2I p3 = { triWidth - sideOffset, triHeight - sideOffset };

Sprite triangle{ {p1, p2, p3} };

int main()
{
    DrawUtils::SetToSystemLocale();


    int rotation = 0;
    while ( true )
    {
        DrawUtils::ResetTerminalCursor();
        DrawUtils::ClearFrame( screen, SHADE_0 );
        DrawUtils::DrawBorderOnFrame( screen );

        rotation = ( rotation + 10 ) % 360;

        DrawUtils::DrawFrame( screen );

        std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );
    }
}