#include "GeoUtils.hpp"
#include "Vec2I.hpp"
#include <cmath>

namespace GeoUtils
{

bool PointOnLine( Vec2I pt, LineI l )
{
    // y = m*x + c
    // y = ((y2 - y1) / (x2 - x1)) * x + c
    // y - c = (y2 - y1) / (x2 - x1) * x
    // (y - c)(x2 - x1) = (y2 - y1) * x
    // (y - c)(x2 - x1) - (y2 - y1) * x = 0 iff (x, y) lie on the line y = m*x + c

    Vec2I xMaxPt = l.p1.x < l.p2.x ? l.p2 : l.p1;
    Vec2I xMinPt = l.p1.x > l.p2.x ? l.p2 : l.p1;
    int slope = xMaxPt.y < xMinPt.y ? -1 : 1;

    return ( ( pt.y - l.c ) * slope * std::abs( l.p2.x - l.p1.x ) - std::abs( l.p2.y - l.p1.y ) * pt.x ) == 0;
}
bool PointInPolygon( Vec2I pt, const std::vector< Vec2I >& polygonPts )
{
}
} // namespace GeoUtils