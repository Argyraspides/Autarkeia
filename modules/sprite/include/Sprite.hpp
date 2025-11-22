#pragma once

#include "Vec2I.hpp"
#include <vector>

struct Sprite
{
  public:
    Sprite() = default;
    Sprite( const std::vector< Vec2I >& points );

    ~Sprite() = default;

    const std::vector< Vec2I >& GetPointCloud() const;

    Vec2I GetCentroid() const;

    void ChangePoint( size_t idx, Vec2I newPt );

  private:
    std::vector< Vec2I > m_points; // Original points used to construct the sprite
    Vec2I m_centroid;
};