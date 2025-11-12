#include "Sprite.hpp"
#include <iostream>
#include <utility>

Sprite::Sprite()
    : m_originalPoints{},
      m_modifiedPoints{}
{
}

Sprite::Sprite( const std::vector< Vec2I >& points )
    : m_originalPoints( points ),
      m_modifiedPoints( points )
{
}

Sprite::Sprite( Sprite&& sprite )
{
    m_originalPoints = std::move( sprite.m_originalPoints );
    m_modifiedPoints = std::move( sprite.m_modifiedPoints );
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
    if ( idx >= m_modifiedPoints.size() )
    {
        std::cout << "Sprite::ChangePoint(size_t, Vec2I) - ATTEMPT TO WRITE OUT OF BOUNDS" << std::endl;
        return;
    }

    m_modifiedPoints[ idx ] = newPoint;
}