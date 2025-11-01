#include "Sprite.hpp"
#include <cassert>
#include <limits>

Sprite::Sprite( size_t width, size_t height, Vec2I center )
    : frame{ width, height }
{
    size_t defaultCenterX = width / 2;
    size_t defaultCenterY = height / 2;
    assert( defaultCenterX < std::numeric_limits< int >::max() && defaultCenterY < std::numeric_limits< int >::max() &&
            "Sprite too big" );

    center.x = static_cast< int >( defaultCenterX );
    center.y = static_cast< int >( defaultCenterY );
}