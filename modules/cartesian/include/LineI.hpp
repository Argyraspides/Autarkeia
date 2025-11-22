#include "Vec2I.hpp"

struct LineI
{
    LineI();
    LineI( Vec2I p1, Vec2I p2 );
    Vec2I p1, p2;
    int c;
};