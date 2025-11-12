#include "Vec2I.hpp"
#include <vector>

struct Sprite
{
  public:
    Sprite() = delete;
    Sprite( const std::vector< Vec2I >& points );

    ~Sprite() = default;

    const std::vector< Vec2I >& GetPointCloudOriginal() const;
    const std::vector< Vec2I >& GetPointCloudModified() const;

    void ChangePoint( size_t idx, Vec2I newPt );

  private:
    std::vector< Vec2I > m_originalPoints; // Original points used to construct the sprite
    std::vector< Vec2I > m_modifiedPoints; // What is actually displayed
};