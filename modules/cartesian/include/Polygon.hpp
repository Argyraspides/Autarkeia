#include "LineI.hpp"

class Polygon
{
  public:
    Polygon();
    Polygon( const std::vector< Vec2I >& points );
    const std::vector< LineI >& GetLines() const;

    void Center();

  private:
    std::vector< LineI > m_lines;
    Vec2I m_centroid;
};