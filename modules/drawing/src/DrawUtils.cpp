//
// Created by gaugamela on 10/18/25.
//
#include "DrawUtils.hpp"
#include "Frame.hpp"
#include "Vec2I.hpp"
#include <cmath>
#include <iostream>
#include <unistd.h>

namespace DrawUtils
{

void DrawLine( Vec2I p1, // Starting point
               Vec2I p2, // Ending point
               Frame& frameBuffer,
               char drawChar,
               FrameSection section )
{
    if ( frameBuffer.Empty() )
        return;

    if ( p1.x == p2.x )
    {
        DrawLineVertical( p1.y, p2.y, p1.x, frameBuffer, drawChar );
        return;
    }

    if ( p1.y == p2.y )
    {
        DrawLineHorizontal( p1.x, p2.x, p1.y, frameBuffer, drawChar );
        return;
    }

    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    // dx*y - dx*b - dy*x = 0
    // or f(x,y) = dx*y - dx*b - dy*x
    // let c = dx*b (constant)
    int c = ( dx * p1.y ) - ( dy * p1.x );

    const int dirX = dx > 0 ? 1 : ( dx == 0 ? 0 : -1 );
    const int dirY = dy > 0 ? 1 : ( dy == 0 ? 0 : -1 );

    const auto fxy = [ dx, dy, c ]( Vec2I p ) -> int { return ( dx * p.y ) - c - ( dy * p.x ); };

    Vec2I currPoint = p1;

    int it = ( dx > dy ) ? abs( dx ) : abs( dy );
    for ( int i = 0; i <= it; i++ )
    {

        if ( !frameBuffer.Write( currPoint.x, currPoint.y, drawChar, section ) )
            break;

        Vec2I nextPoint{};
        // Move in direction with larger delta
        if ( it == abs( dx ) )
        {
            currPoint.x += dirX;
            nextPoint = { currPoint.x, currPoint.y + dirY };
        }
        else
        {
            currPoint.y += dirY;
            nextPoint = { currPoint.x + dirX, currPoint.y };
        }

        int currDist = abs( fxy( currPoint ) );
        int nextDist = abs( fxy( nextPoint ) );

        // nextPoint is closer to line
        if ( nextDist - currDist < 0 )
            currPoint = nextPoint;
    }
}

void DrawLineVertical( int y1, int y2, int x, Frame& frame, char drawChar, FrameSection section )
{
    if ( y1 > y2 )
        std::swap( y1, y2 );

    while ( y1 <= y2 && frame.Write( x, y1++, drawChar, section ) )
        ;
}

void DrawLineHorizontal( int x1, int x2, int y, Frame& frame, char drawChar, FrameSection section )
{

    if ( x1 > x2 )
        std::swap( x1, x2 );

    while ( x1 <= x2 && frame.Write( x1++, y, drawChar, section ) )
        ;
}

void QuickDrawLine( Vec2I p1, // Starting point
                    Vec2I p2, // Ending point
                    Frame& frame,
                    char drawChar,
                    FrameSection section )
{

    if ( p1.x == p2.x )
    {
        DrawLineVertical( p1.y, p2.y, p1.x, frame, drawChar, section );
        return;
    }

    if ( p1.y == p2.y )
    {
        DrawLineHorizontal( p1.x, p2.x, p1.y, frame, drawChar, section );
        return;
    }

    int dx = p2.x - p1.x;
    int dxPolarity = dx < 0 ? -1 : 1;

    int dy = p2.y - p1.y;
    int dyPolarity = dy < 0 ? -1 : 1;

    int dist = 0;

    if ( abs( dx ) >= abs( dy ) )
    {
        int it = abs( dx );
        Vec2I currPt = p1;
        for ( int i = 0; i <= it; i++ )
        {
            if ( dist < 0 )
            {
                currPt.y += dyPolarity;
                dist += dx * dxPolarity;
            }

            if ( !frame.Write( currPt.x, currPt.y, drawChar ) )
                break;

            currPt.x += dxPolarity;
            dist += -dy * dyPolarity;
        }
    }
    else
    {
        int it = abs( dy );
        Vec2I currPt = p1;
        for ( int i = 0; i <= it; i++ )
        {
            if ( dist > 0 )
            {
                currPt.x += dxPolarity;
                dist += -dy * dyPolarity;
            }

            if ( !frame.Write( currPt.x, currPt.y, drawChar ) )
                break;

            currPt.y += dyPolarity;
            dist += dx * dxPolarity;
        }
    }
}

void DrawTriangle( Vec2I p1, Vec2I p2, Vec2I p3, Frame& frame, char drawChar, FrameSection section )
{
    DrawLine( p1, p2, frame, drawChar, section );
    DrawLine( p2, p3, frame, drawChar, section );
    DrawLine( p3, p1, frame, drawChar, section );
}

void QuickDrawTriangle( Vec2I p1, Vec2I p2, Vec2I p3, Frame& frame, char drawChar, FrameSection section )
{
    QuickDrawLine( p1, p2, frame, drawChar, section );
    QuickDrawLine( p2, p3, frame, drawChar, section );
    QuickDrawLine( p3, p1, frame, drawChar, section );
}

void DrawPixel( Vec2I p, Frame& frame, char drawChar, FrameSection section )
{
    frame.Write( p.x, p.y, drawChar, section );
}

void Clear( Frame& frame, char clearChar )
{
    for ( int y = 0; y < frame.Height(); y++ )
        for ( int x = 0; x < frame.Width(); x++ )
            frame.Write( x, y, clearChar );
}

void ClearScreen()
{
    // Run 'strace clear > /dev/null' to find out how this works.
    // Check the write() syscall at the end
    write( STDOUT_FILENO, "\33[H\33[2J\33[3J", 11 );
}

void Draw( Frame& frame )
{
    std::cout << frame.Buffer();
}

} // namespace DrawUtils