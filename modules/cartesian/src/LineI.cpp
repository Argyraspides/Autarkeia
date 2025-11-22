#include "LineI.hpp"
#include <cmath>

static int GetC( Vec2I p1, Vec2I p2 )
{
    // y = mx + c
    // y - mx = c
    // y - (y2 - y1)/(x2 -x1) * x = c
    Vec2I xMaxPt = p1.x < p2.x ? p2 : p1;
    Vec2I xMinPt = p1.x > p2.x ? p2 : p1;

    int slope = xMaxPt.y < xMinPt.y ? -1 : 1;

    int dy = std::abs( p2.y - p1.y );
    int dx = std::abs( p2.x - p1.x );

    Vec2I p3 = ( p1 + p2 ) / 2;
}

LineI::LineI()
{
}

LineI::LineI( Vec2I p1, Vec2I p2 )
{
    c = GetC( p1, p2 );
}