#include "DrawUtils.hpp"
#include <thread>

constexpr size_t width = 40;
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
    Vec2I dvd = { 15, 13 };
    Vec2I dvdTrajectory = { 1, -1 };

    Frame frame( width, height );

    while ( true )
    {
        DrawUtils::ClearScreen();
        DrawUtils::Clear( frame, ' ' );

        DrawBorder( frame );

        DrawUtils::DrawPixel( dvd, frame, 'D' );

        Vec2I nextDvdPos = dvd + dvdTrajectory;
        if ( nextDvdPos.x >= frame.Width() - 1 || nextDvdPos.x <= 0 )
            dvdTrajectory.x *= -1;
        if ( nextDvdPos.y >= frame.Height() - 1 || nextDvdPos.y <= 0 )
            dvdTrajectory.y *= -1;

        dvd = dvd + dvdTrajectory;

        DrawUtils::Draw( frame );

        std::this_thread::sleep_for( std::chrono::milliseconds( 150 ) );
    }
}