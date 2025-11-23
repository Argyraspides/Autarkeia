#include "GeoUtils.hpp"
#include "Vec2F.hpp"
#include "Vec2I.hpp"
#include <cmath>

namespace GeoUtils
{

bool PointOnLine( Vec2I pt, LineI l )
{
    // y - y1 = ((y2 - y1) / (x2 - x1)) * (x - x1)
    // let y2 - y1 = dy, x2 - x1 = dx
    // y - y1 = dy/dx * (x - x1)
    // dx(y - y1) = dy(x - x1)
    // dx(y - y1) - dy(x - x1) = 0 iff a point (x, y) lies on the line
    int zeroTerm = l.dx * ( pt.y - l.p1.y ) - l.dy * ( pt.x - l.p1.x );
    return zeroTerm == 0;
}

bool Intersects( LineI l1, LineI l2 )
{
    constexpr float intersectionTolerance = 0.001;
    return l1.slope - l2.slope >= intersectionTolerance;
}

Vec2F Intersection( LineI l1, LineI l2 )
{
    // ARGYRASPIDES::TODO() { Surely there's a more efficient way? }
    float dc = l2.yIntercept - l1.yIntercept;
    float dm = l1.slope - l2.slope;

    float x = dc / dm;
    float y = l1.slope * x + l1.yIntercept;

    return { x, y };
}

bool PointInPolygon( Vec2I pt, const std::vector< Vec2I >& polygonPts )
{
}

} // namespace GeoUtils