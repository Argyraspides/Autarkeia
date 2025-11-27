#include "GeoUtils.hpp"
#include "Polygon.hpp"
#include "Vec2F.hpp"
#include "Vec2I.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <optional>

namespace GeoUtils
{

bool PointOnLine( const Vec2I pt, const LineI l )
{
    // y - y1 = ((y2 - y1) / (x2 - x1)) * (x - x1)
    // let y2 - y1 = dy, x2 - x1 = dx
    // y - y1 = dy/dx * (x - x1)
    // dx(y - y1) = dy(x - x1)
    // dx(y - y1) - dy(x - x1) = 0 iff a point (x, y) lies on the line
    int zeroTerm = l.dx * ( pt.y - l.p1.y ) - l.dy * ( pt.x - l.p1.x );
    return zeroTerm == 0;
}

std::optional< Vec2F > Intersection( const LineI l1, const LineI l2 )
{
    constexpr float intersectionTolerance = 0.001;
    bool willIntersect = std::abs( l1.slope - l2.slope ) >= intersectionTolerance;

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

bool Intersects( const LineI l1, const LineI l2 )
{
    std::optional< Vec2F > intersectionPt = Intersection( l1, l2 );

    if ( !intersectionPt )
        return false;

    int l1MinX = std::min( l1.p1.x, l1.p2.x );
    int l1MaxX = std::max( l1.p1.x, l1.p2.x );

    int l1MinY = std::min( l1.p1.y, l1.p2.y );
    int l1MaxY = std::max( l1.p1.y, l1.p2.y );

    int l2MinX = std::min( l2.p1.x, l2.p2.x );
    int l2MaxX = std::max( l2.p1.x, l2.p2.x );

    int l2MinY = std::min( l2.p1.y, l2.p2.y );
    int l2MaxY = std::max( l2.p1.y, l2.p2.y );

    bool withinL1XBounds = intersectionPt->x >= l1MinX && intersectionPt->x <= l1MaxX;
    bool withinL2XBounds = intersectionPt->x >= l2MinX && intersectionPt->x <= l2MaxX;

    bool withinL1YBounds = intersectionPt->y >= l1MinY && intersectionPt->y <= l1MaxY;
    bool withinL2YBounds = intersectionPt->y >= l2MinY && intersectionPt->y <= l2MaxY;

    if ( !withinL1XBounds || !withinL2XBounds || !withinL1YBounds || !withinL2YBounds )
        return false;

    return true;
}

bool PointInPolygon( const Vec2I pt, const std::vector< Vec2I >& polygonPoints )
{
    // Ray parallel to x axis going through pt
    const LineI ray{ pt, Vec2I( std::numeric_limits< int >::max(), pt.y ) };

    unsigned int intersections = 0;

    for ( int i = 0; i < polygonPoints.size() - 1; i++ )
    {
        LineI line{ polygonPoints[ i ], polygonPoints[ i + 1 ] };
        if ( Intersects( line, ray ) )
            ++intersections;
    }

    LineI lineFinal{ polygonPoints.front(), polygonPoints.back() };
    if ( Intersects( lineFinal, ray ) )
        ++intersections;

    // If odd, we are inside polygon
    return ( intersections & 1 );
}

} // namespace GeoUtils