#include "Sprite.hpp"
#include <iostream>

Sprite::Sprite( const std::vector< Vec2I >& points )
    : m_originalPoints( points ), m_modifiedPoints( points )
{
}

const std::vector< Vec2I >& Sprite::GetPointCloudOriginal() const
{
    return m_originalPoints;
}

const std::vector< Vec2I >& Sprite::GetPointCloudModified() const 
{
    return m_modifiedPoints;
}

void Sprite::ChangePoint( size_t idx, Vec2I newPoint )
{
    if ( idx >= m_modifiedPoints.size() ) {
        std::cout << "Sprite::ChangePoint(size_t, Vec2I) - ATTEMPT TO WRITE OUT OF BOUNDS" << std::endl;
        return;
    }

    m_modifiedPoints[ idx ] = newPoint;
}