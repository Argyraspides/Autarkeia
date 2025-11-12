#include "Sprite.hpp"
#include <iostream>
#include <cassert>

Sprite::Sprite( const std::vector< Vec2I >& points )
    : m_originalPoints( points )
{
}

const std::vector< Vec2I >& Sprite::GetPointCloudOriginal() const
{
    return m_originalPoints;
}

void Sprite::ChangePoint( size_t idx, Vec2I newPoint )
{
    if ( idx >= m_modifiedPoints.size() )
        std::cout << "Sprite::ChangePoint(size_t, Vec2I) - ATTEMPT TO WRITE OUT OF BOUNDS" << std::endl;

    m_modifiedPoints[ idx ] = newPoint;
}