#include "LineI.hpp"
#include <vector>

namespace GeoUtils
{
bool PointOnLine( Vec2I pt, LineI l );
bool PointInPolygon( Vec2I pt, const std::vector< Vec2I >& polygonPts );
} // namespace GeoUtils