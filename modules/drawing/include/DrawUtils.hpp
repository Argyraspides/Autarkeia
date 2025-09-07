//
// Created by gaugamela on 8/23/25.
//

#ifndef DRAWUTILS_HPP
#define DRAWUTILS_HPP

#include "Frame.hpp"
#include "Vec2I.hpp"
#include <cmath>
#include <cstring>
#include <iostream>
#include <unistd.h>

namespace DrawUtils
{

inline void DrawLine( const Vec2I& p1, // Starting point
                      const Vec2I& p2, // Ending point
                      Frame& frameBuffer,
                      const char& drawChar )
{
    if ( frameBuffer.Empty() )
    {
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

    const auto fxy = [ dx, dy, c ]( const Vec2I& p ) -> int { return ( dx * p.y ) - c - ( dy * p.x ); };

    Vec2I currPoint = p1;

    int it = ( dx > dy ) ? abs( dx ) : abs( dy );
    for ( int i = 0; i <= it; i++ )
    {

        if ( !frameBuffer.Write( currPoint.x, currPoint.y, drawChar ) )
        {
            break;
        }

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
        {
            currPoint = nextPoint;
        }
    }
}

inline void DrawLineVertical(
    int y1, int y2, const int x, Frame& frame, const char& drawChar )
{
    if ( y1 > y2 )
    {
        std::swap( y1, y2 );
    }

    while ( y1 <= y2 && frame.Write(x, y1++, drawChar) );
}

inline void DrawLineHorizontal(
    int x1, int x2, const int y, Frame& frame, const char& drawChar )
{

    if ( x1 > x2 )
    {
        std::swap( x1, x2 );
    }

    while ( x1 <= x2 && frame.Write(x1++, y, drawChar) );
}

inline void QuickDrawLine( const Vec2I& p1, // Starting point
                           const Vec2I& p2, // Ending point
                           Frame& frame,
                           const char& drawChar )
{

    if ( p1.x == p2.x )
    {
        DrawLineVertical( p1.y, p2.y, p1.x, frame, drawChar );
        return;
    }

    if ( p1.y == p2.y )
    {
        DrawLineHorizontal( p1.x, p2.x, p1.y, frame, drawChar );
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

            if (!frame.Write(currPt.x, currPt.y, drawChar))
            {
                break;
            }

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

            if (!frame.Write(currPt.x, currPt.y, drawChar))
            {
                break;
            }

            currPt.y += dyPolarity;
            dist += dx * dxPolarity;
        }
    }
}

inline void DrawTriangle( const Vec2I& p1,
                          const Vec2I& p2,
                          const Vec2I& p3,
                          Frame& frame,
                          const char& drawChar )
{
    DrawLine( p1, p2, frame, drawChar );
    DrawLine( p2, p3, frame, drawChar );
    DrawLine( p3, p1, frame, drawChar );
}

inline void QuickDrawTriangle( const Vec2I& p1,
                               const Vec2I& p2,
                               const Vec2I& p3,
                               Frame& frame,
                               const char& drawChar )
{
    QuickDrawLine( p1, p2, frame, drawChar );
    QuickDrawLine( p2, p3, frame, drawChar );
    QuickDrawLine( p3, p1, frame, drawChar );
}

inline void DrawPixel( const Vec2I& p, Frame& frame, const char& drawChar )
{
    frame.Write(p.x, p.y, drawChar);
}

inline void Clear( Frame& frame, const char& clearChar )
{
    for (int y = 0; y < frame.Height(); y++)
        for (int x = 0; x < frame.Width(); x++)
            frame.Write(x, y, clearChar);
}

inline void ClearScreen()
{
    // Run 'strace clear > /dev/null' to find out how this works.
    // Check the write() syscall at the end
    write(STDOUT_FILENO, "\33[H\33[2J\33[3J", 11);
}

inline void Draw( Frame& frame )
{
    std::cout << frame.Buffer();
}

} // namespace DrawUtils

#endif // DRAWUTILS_HPP
