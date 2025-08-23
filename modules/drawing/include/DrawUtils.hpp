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

inline void DrawLine( const Vec2I& p1,
                      const Vec2I& p2,
                      std::vector< std::vector< char > >& frameBuf,
                      const char& drawChar )
{
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int c = ( dx * p1.y ) - ( dy * p1.x );

    const int dirX = dx > 0 ? 1 : (dx == 0 ? 0 : -1);
    const int dirY = dy > 0 ? 1 : (dy == 0 ? 0 : -1);

    const auto fxy = [ dx, dy, c ]( const Vec2I& p ) -> int { return ( dx * p.y ) - c - ( dy * p.x ); };

    Vec2I currPoint = p1;

    if ( dx > dy )
    {
        for ( int i = 0; i < abs(dx); i++ )
        {
            if ( currPoint.y < 0 || currPoint.y > frameBuf.size() || currPoint.x < 0 ||
                 currPoint.x > frameBuf[ 0 ].size() )
            {
                continue;
            }
            frameBuf[ currPoint.y ][ currPoint.x ] = drawChar;
            currPoint.x += dirX;

            int currYDist = fxy( currPoint );
            int nextYDist = fxy( { currPoint.x, currPoint.y + dirY } );

            currPoint.y += ( nextYDist < currYDist ) ? dirY : 0;
        }
    }
    else
    {
        for ( int i = 0; i < abs(dy); i++ )
        {
            if ( currPoint.y < 0 || currPoint.y > frameBuf.size() || currPoint.x < 0 ||
                 currPoint.x > frameBuf[ 0 ].size() )
            {
                continue;
            }
            frameBuf[ currPoint.y ][ currPoint.x ] = drawChar;
            currPoint.y += dirY;

            int currXDist = fxy( currPoint );
            int nextXDist = fxy( { currPoint.x + dirX, currPoint.y } );

            currPoint.x += ( nextXDist < currXDist ) ? dirX : 0;
        }
    }
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
