#pragma once
#include "Vec2I.hpp"

struct LineI
{
    LineI() = delete;
    LineI( Vec2I p1, Vec2I p2 );
    void Move( Vec2I offset );

    // p2.x is guaranteed to be in front of p1.x
    Vec2I p1, p2;

    int dx; // dist from p1.x to p2.x
    int dy; // dist from p1.y to p2.y

    float slope;
    float yIntercept;

    enum Orientation
    {
        HORIZONTAL,
        VERTICAL,
        SLOPED_POSITIVE,
        SLOPED_NEGATIVE
    } orientation;
};