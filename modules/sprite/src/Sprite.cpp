#include "Sprite.hpp"
#include <iostream>
#include <numeric>

Sprite::Sprite( const std::vector< Vec2I >& points )
    : m_originalPoints( points ),
      m_modifiedPoints( points )
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

Vec2I Sprite::GetCentroidModified() const
{
    return std::accumulate( m_modifiedPoints.begin(), m_modifiedPoints.end(), Vec2I{ 0, 0 } ) / m_modifiedPoints.size();
}

void Sprite::ChangePoint( size_t idx, Vec2I newPoint )
{
    if ( idx >= m_modifiedPoints.size() )
    {
        std::cout << "Sprite::ChangePoint(size_t, Vec2I) - ATTEMPT TO WRITE OUT OF BOUNDS" << std::endl;
        return;
    }

    m_modifiedPoints[ idx ] = newPoint;
}