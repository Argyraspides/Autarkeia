#include "Polygon.hpp"
#include <numeric>

Polygon::Polygon()
{
}

Polygon::Polygon( const std::vector< Vec2I >& points )
{
    assert( points.size() >= 3 && "A polygon cannot have less than 3 points dummy" );

    m_centroid = std::accumulate( points.begin(), points.end(), Vec2I{ 0, 0 } ) / points.size();

    for ( int i = 0; i < points.size() - 1; i++ )
        m_lines.push_back( LineI{ points[ i ], points[ i + 1 ] } );

    m_lines.push_back( LineI{ points.front(), points.back() } );
}

void Polygon::Center()
{
    for ( LineI& line : m_lines )
        line.Move( m_centroid * -1 );
    m_centroid = { 0, 0 };
}

const std::vector< LineI >& Polygon::GetLines() const
{
    return m_lines;
}