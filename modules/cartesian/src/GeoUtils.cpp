#include "GeoUtils.hpp"
#include "Vec2I.hpp"
#include <cmath>
#include <limits>

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
    if ( l1.slope - l2.slope <= std::numeric_limits< float >::epsilon() )
        return false;
}

bool PointInPolygon( Vec2I pt, const std::vector< Vec2I >& polygonPts )
{
}

} // namespace GeoUtils