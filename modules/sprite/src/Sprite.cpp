#include "Sprite.hpp"
#include <iostream>
#include <numeric>

Sprite::Sprite( const std::vector< Vec2I >& points )
    : spriteColor( Color::WHITE ),
      m_originalPoints( points ),
      m_modifiedPoints( points )
{
    Vec2I centroid =
        std::accumulate( m_originalPoints.begin(), m_originalPoints.end(), Vec2I{ 0, 0 } ) / m_originalPoints.size();
    bool centroidZero = centroid == Vec2I{ 0, 0 };

    if ( !centroidZero )
    {
        for ( Vec2I& v : m_originalPoints )
            v = v - centroid;

        for ( Vec2I& v : m_modifiedPoints )
            v = v - centroid;
    }
}

const std::vector< Vec2I >& Sprite::GetPointCloud() const
{
    return m_modifiedPoints;
}

const std::vector< Vec2I >& Sprite::GetBasePointCloud() const
{
    return m_originalPoints;
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