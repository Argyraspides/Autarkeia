#include "Frame.hpp"

struct Sprite
{
public:
    Sprite( size_t width, size_t height, Vec2I center = {});
    ~Sprite() = default;

    const Frame& GetFrameC() const;
    Frame& GetFrame();
    Vec2I GetCenter() const;

private:
    Frame m_frame;     
    Vec2I m_center;
};