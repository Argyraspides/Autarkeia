#include "Sprite.hpp"
#include <cassert>
#include <limits>

Sprite::Sprite( size_t width, size_t height, Vec2I center )
    : m_frame{ width, height }
{
    size_t defaultCenterX = width / 2;
    size_t defaultCenterY = height / 2;
    assert( defaultCenterX < std::numeric_limits< int >::max() && defaultCenterY < std::numeric_limits< int >::max() &&
            "Sprite too big" );

    this->m_center.x = static_cast< int >( defaultCenterX );
    this->m_center.y = static_cast< int >( defaultCenterY );
}

const Frame& Sprite::GetFrameC() const
{
    return m_frame;
}

Frame& Sprite::GetFrame() 
{
    return m_frame;
}

Vec2I Sprite::GetCenter() const
{
    return m_center;
}
