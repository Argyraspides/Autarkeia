#pragma once

#include <vector>
#include "Polygon.hpp"

struct Sprite
{
  public:
    Sprite() = default;
    Sprite( const std::vector< Vec2I >& points );

    ~Sprite() = default;

    const std::vector< Vec2I >& GetPointCloud() const;
    const std::vector< Vec2I >& GetBasePointCloud() const;

    void ChangePoint( size_t idx, Vec2I newPt );

  private:
    // We always perform rotations based on the original points to prevent precision loss over time.
    // Thus we keep track of the original sprite and modified sprite separately. 
    std::vector< Vec2I > m_originalPoints;
    std::vector< Vec2I > m_modifiedPoints;

    Vec2I m_centroid;
};