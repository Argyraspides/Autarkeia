#include "Sprite.hpp"
#include <iostream>
#include <numeric>

Sprite::Sprite( const std::vector< Vec2I >& points )
    : m_points( points ),
      m_centroid( GetCentroid() )
{
    bool centroidZero = m_centroid == Vec2I{ 0, 0 };

    if ( !centroidZero )
    {
        for ( Vec2I& v : m_points )
            v = v - m_centroid;
    }
}

const std::vector< Vec2I >& Sprite::GetPointCloud() const
{
    return m_points;
}

Vec2I Sprite::GetCentroid() const
{
    Vec2I centroid = std::accumulate( m_points.begin(), m_points.end(), Vec2I{ 0, 0 } ) / m_points.size();
    return centroid;
}

void Sprite::ChangePoint( size_t idx, Vec2I newPoint )
{
    if ( idx >= m_points.size() )
    {
        std::cout << "Sprite::ChangePoint(size_t, Vec2I) - ATTEMPT TO WRITE OUT OF BOUNDS" << std::endl;
        return;
    }

    m_points[ idx ] = newPoint;
}