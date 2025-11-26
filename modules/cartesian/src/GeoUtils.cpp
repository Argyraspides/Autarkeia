#include "GeoUtils.hpp"
#include "Polygon.hpp"
#include "Vec2F.hpp"
#include "Vec2I.hpp"
#include <algorithm>
#include <cmath>
#include <optional>

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

std::optional< Vec2F > Intersection( LineI l1, LineI l2 )
{
    // ARGYRASPIDES::TODO() { Surely there's a more efficient way? }
    constexpr float intersectionTolerance = 0.001;
    bool willIntersect = l1.slope - l2.slope >= intersectionTolerance;

    if ( !willIntersect )
        return std::nullopt;

    if ( l1.orientation == LineI::Orientation::VERTICAL && l2.orientation == LineI::Orientation::VERTICAL )
        return std::nullopt;

    if ( l1.orientation == LineI::Orientation::HORIZONTAL && l2.orientation == LineI::Orientation::HORIZONTAL )
        return std::nullopt;

    float dc = l2.yIntercept - l1.yIntercept;
    float dm = l1.slope - l2.slope;

    float x = dc / dm;
    float y = l1.slope * x + l1.yIntercept;

    return Vec2F{ x, y };
}

bool Intersects( LineI l1, LineI l2 )
{

}

bool PointInPolygon( Vec2I pt, const Polygon& polygon )
{
    // Ray parallel to x axis going through pt
    const LineI ray{ pt, Vec2I( pt.x + 1, pt.y ) };

    unsigned int intersections = 0;
    const std::vector< LineI >& polygonEdges = polygon.GetLines();
    for ( const LineI line : polygonEdges )
    {
        if ( Intersects( line, ray ) )
            continue;

        ++intersections;
    }

    // If odd, we are inside polygon
    return ( intersections & 1 );
}

} // namespace GeoUtils