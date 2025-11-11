#include <vector>
#include "Vec2I.hpp"

struct SpritePC
{
public:
    SpritePC() = default;
    ~SpritePC() = default;
    std::vector<Vec2I> points;
    std::vector<Vec2I> rotatedPoints;
};