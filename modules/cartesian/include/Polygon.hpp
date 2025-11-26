#include "LineI.hpp"

class Polygon
{
  public:
    Polygon();
    Polygon( const std::vector< Vec2I >& points );
    const std::vector< LineI >& GetLines() const;

    // Moves polygon such that its centroid is (0,0)
    void Center();

  private:
    std::vector< LineI > m_lines;
    Vec2I m_centroid;
};