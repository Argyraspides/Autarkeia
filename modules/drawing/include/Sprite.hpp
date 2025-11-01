#include "Frame.hpp"
struct Sprite
{
public:
    Sprite( size_t width, size_t height, Vec2I center = {});
    ~Sprite() = default;
    Frame frame;     
    Vec2I center;
};