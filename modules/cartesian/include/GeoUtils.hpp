#include "LineI.hpp"
#include <vector>

namespace GeoUtils
{
bool PointOnLine( Vec2I pt, LineI l );
bool Intersects( LineI l1, LineI l2 );
bool PointInPolygon( Vec2I pt, const std::vector< Vec2I >& polygonPts );
} // namespace GeoUtils