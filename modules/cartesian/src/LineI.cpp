#include "LineI.hpp"
#include <cmath>
#include <limits>

LineI::LineI( Vec2I p1, Vec2I p2 )
    : p1{ p1 },
      p2{ p2 }
{
    // ARGYRASPIDES()::DESIGN DECISION
    // {
    //  All cartesian representations in the engine are in normal cartesian space
    //  not the typical convention of top-left corner of (0,0)
    // }

    this->p2 = p1.x > p2.x ? p1 : p2;
    this->p1 = p1.x < p2.x ? p1 : p2;

    this->dy = this->p2.y - this->p1.y;
    this->dx = this->p2.x - this->p1.x;

    if ( p1.x == p2.x )
    {
        orientation = Orientation::VERTICAL;
        yIntercept = std::numeric_limits< float >::quiet_NaN();
        return;
    }

    if ( p1.y == p2.y )
    {
        orientation = Orientation::HORIZONTAL;
        yIntercept = p1.y;
        return;
    }

    // y = m*x + c
    // y = ((y2 - y1) / (x2 - x1)) * x + c
    // y - ((y2 - y1) / (x2 - x1)) * x = c
    // y - dy/dx * x = c where dy/dx = the slope
    this->slope = static_cast< float >( dy ) / static_cast< float >( dx );
    orientation = slope < 0 ? Orientation::SLOPED_NEGATIVE : Orientation::SLOPED_POSITIVE;
    this->yIntercept = static_cast< float >( p1.y ) - slope * p2.x;
}