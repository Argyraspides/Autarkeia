//
// Created by gaugamela on 8/23/25.
//

#ifndef DRAWUTILS_HPP
#define DRAWUTILS_HPP

#include "Vec2I.hpp"
#include <cmath>
#include <iostream>
#include <vector>

namespace DrawUtils
{

inline void DrawLine( const Vec2I& p1, // Starting point
                      const Vec2I& p2, // Ending point
                      std::vector< std::vector< char > >& frameBuf,
                      const char& drawChar )
{
    if ( frameBuf.empty() || frameBuf[ 0 ].empty() )
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
        if  (   currPoint.y < 0                     ||
                currPoint.y >= frameBuf.size()      ||
                currPoint.x < 0                     ||
                currPoint.x >= frameBuf[ 0 ].size()
            )
        {
            break;
        }

        frameBuf[ currPoint.y ][ currPoint.x ] = drawChar;

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

// TODO::GAUGEMALA() { Only works in +ve x and y direction, though way more efficient than DrawLine. Add all cases later }
inline void DrawLineV2( const Vec2I& p1,    // Starting point
                      const Vec2I& p2,      // Ending point
                      std::vector< std::vector< char > >& frameBuf,
                      const char& drawChar )
{
    if ( frameBuf.empty() || frameBuf[ 0 ].empty() )
    {
        return;
    }

    const int dx = p2.x - p1.x;
    const int dy = p2.y - p1.y;

    Vec2I currentPoint = p1;
    int err = (2 * dy) - (2 * dx * p1.y) + dy;

    for (int i = p1.x; i <= p2.x; i++)
    {
        frameBuf[currentPoint.y][currentPoint.x] = drawChar;

        if ( err > 0 )
        {
            ++currentPoint.y;
            err += -dx;
        }

        ++currentPoint.x;
        err += dy;
    }

}

// TODO::GAUGAMELA() { Maybe there's a more efficient way to draw specifically a triangle? }
inline void DrawTriangle( const Vec2I& p1,
                          const Vec2I& p2,
                          const Vec2I& p3,
                          std::vector< std::vector< char > >& frameBuf,
                          const char& drawChar )
{
    DrawLine( p1, p2, frameBuf, drawChar );
    DrawLine( p2, p3, frameBuf, drawChar );
    DrawLine( p3, p1, frameBuf, drawChar );
}

inline void DrawPixel( const Vec2I& p, std::vector< std::vector< char > >& frameBuf, const char& drawChar )
{
    if ( frameBuf.empty() || frameBuf[ 0 ].empty() )
    {
        return;
    }

    if ( p.x < 0 || p.x >= frameBuf[0].size() || p.y < 0 || p.y >= frameBuf.size() )
    {
        return;
    }

    frameBuf[ p.y ][ p.x ] = drawChar;
}

inline void Clear( std::vector< std::vector< char > >& frameBuf, const char& clearChar )
{
    for ( int i = 0; i < frameBuf.size(); i++ )
    {
        for ( int j = 0; j < frameBuf[ 0 ].size(); j++ )
        {
            frameBuf[ i ][ j ] = clearChar;
        }
    }
}

inline void Draw( const std::vector< std::vector< char > >& frameBuf )
{
    for ( int i = 0; i < frameBuf.size(); i++ )
    {
        for ( int j = 0; j < frameBuf[ 0 ].size(); j++ )
        {
            std::cout << frameBuf[ i ][ j ];
        }
        std::cout << '\n';
    }
}

} // namespace DrawUtils

#endif // DRAWUTILS_HPP
