#include "DrawUtils.hpp"
#include <thread>

constexpr size_t width = 20;
constexpr size_t height = 20;


void DrawBorder(Frame& f)
{
    DrawUtils::QuickDrawLine( { 0, 0 }, { width - 1, 0 }, f, '-' );
    DrawUtils::QuickDrawLine( { 0, height - 1 }, { width - 1, height - 1 }, f, '-' );
    DrawUtils::QuickDrawLine( { 0, 0 }, { 0, height - 1 }, f, '|' );
    DrawUtils::QuickDrawLine( { width - 1, 0 }, { width - 1, height - 1 }, f, '|' );
}

int main()
{
    Vec2I b = { width / 2, height / 2 };
    Vec2I bTraj = { width / 5, height / 10 };

    Frame f( width, height );

    while ( true )
    {
        DrawUtils::ClearScreen();
        DrawUtils::Clear( f, ' ' );

        DrawBorder( f );

        DrawUtils::DrawPixel( b, f, '.' );

        Vec2I nextB = b + bTraj;

        if ( nextB.x >= f.Width() || nextB.x < 0 )
            bTraj.x *= -1;

        if ( nextB.y >= f.Height() || nextB.y < 0 )
            bTraj.y *= -1;

        b = b + bTraj;

        DrawUtils::Draw( f );
        std::this_thread::sleep_for( std::chrono::milliseconds( 150 ) );
    }
}