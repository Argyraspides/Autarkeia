//
// Created by Argyraspides on 9/7/25.
//

#include "Frame.hpp"
#include "Vec2I.hpp"
#include <cassert>
#include <limits>
#include <stdexcept>

static constexpr char DEFAULT_INIT_CHAR = '.';
static constexpr Vec2I INVALID_POINT = { std::numeric_limits< int >::quiet_NaN(),
                                         std::numeric_limits< int >::quiet_NaN() };

Frame::Frame( size_t width, size_t height )
    : m_frameWidth( width ),
      m_frameHeight( height )
{
    m_buffer = std::string( ( width * height ) + height, DEFAULT_INIT_CHAR );

    for ( int i = width; i < m_buffer.size(); i += ( width + 1 ) )
        m_buffer[ i ] = '\n';

    for ( Vec2I& v : m_frameSectionOffsets )
        v = INVALID_POINT;

    for ( Vec2I& v : m_frameSectionDimensions )
        v = INVALID_POINT;
}

Frame::~Frame()
{
}

bool Frame::Write( int x, int y, char dat, FrameSection section )
{
    ValidateSection( section );

    if ( Empty() )
        return false;
    if ( x < 0 || x >= m_frameWidth || y < 0 || y >= m_frameHeight )
        return false;

    if ( section == FrameSection::NONE )
    {
        // m_frameWidth + 1 because the end of each row is a newline that we forbid writing to
        m_buffer[ y * ( m_frameWidth + 1 ) + x ] = dat;
        return true;
    }

    x += m_frameSectionOffsets[ static_cast< size_t >( section ) ].x;
    y += m_frameSectionOffsets[ static_cast< size_t >( section ) ].y;

    Vec2I maxFrameDim = Vec2I{ x, y } + m_frameSectionDimensions[ static_cast< size_t >( section ) ];
    if ( x >= maxFrameDim.x || y >= maxFrameDim.y )
        return false;
    else if ( x < 0 || x >= m_frameWidth || y < 0 || y >= m_frameHeight )
        return false;

    m_buffer[ y * ( m_frameWidth + 1 ) + x ] = dat;

    return true;
}

bool Frame::Write( Vec2I point, char dat, FrameSection section )
{
    ValidateSection( section );
    return Write( point.x, point.y, dat, section );
}

char Frame::At( int x, int y ) const
{
    if ( x < 0 || x >= m_frameWidth || y < 0 || y >= m_frameHeight )
        throw std::out_of_range( "Cannot access (x,y) coordinate -- out of bounds" );

    // m_frameWidth + 1 because the end of each row is a newline that we forbid reading from
    return m_buffer[ y * ( m_frameWidth + 1 ) + x ];
}

void Frame::SetSection( FrameSection section, Vec2I offset, Vec2I dimension )
{
    ValidateSection( section );

    m_frameSectionDimensions[ static_cast< size_t >( section ) ] = dimension;
    m_frameSectionOffsets[ static_cast< size_t >( section ) ] = offset;
}

const std::string& Frame::Buffer()
{
    return m_buffer;
}

void Frame::ValidateSection( FrameSection section )
{
    assert( section != FrameSection::MAX && section != FrameSection::INVALID );
}

bool Frame::Empty() const
{
    return m_buffer.empty();
}

int Frame::Width() const
{
    return m_frameWidth;
}

int Frame::Height() const
{
    return m_frameHeight;
}
int Frame::FlatSize() const
{
    return m_frameWidth * m_frameHeight;
}
