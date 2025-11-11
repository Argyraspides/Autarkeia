//
// Created by Argyraspides on 9/7/25.
//

#include "Frame.hpp"
#include "Characters.hpp"
#include "Vec2I.hpp"
#include <array>
#include <cassert>
#include <limits>
#include <memory>
#include <utility>

static constexpr wchar_t DEFAULT_INIT_CHAR = '.';
static constexpr Vec2I INVALID_POINT = { std::numeric_limits< int >::quiet_NaN(),
                                         std::numeric_limits< int >::quiet_NaN() };

Frame::Frame( size_t width, size_t height )
    : m_frameWidth( width ),
      m_frameHeight( height )
{
    m_buffer = std::make_unique< std::vector< std::vector< wchar_t > > >( height, std::vector< wchar_t >( width ) );

    m_frameSectionOffsets = std::make_unique< std::array< Vec2I, static_cast< size_t >( FrameSection::MAX ) > >();
    for ( Vec2I& v : *m_frameSectionOffsets )
        v = INVALID_POINT;

    m_frameSectionDimensions = std::make_unique< std::array< Vec2I, static_cast< size_t >( FrameSection::MAX ) > >();
    for ( Vec2I& v : *m_frameSectionDimensions )
        v = INVALID_POINT;
}

Frame::Frame( Frame&& otherFrame )
{
    m_frameWidth = otherFrame.m_frameWidth;
    m_frameHeight = otherFrame.m_frameHeight;

    m_buffer = std::move( otherFrame.m_buffer );

    m_frameSectionDimensions = std::move( otherFrame.m_frameSectionDimensions );
    m_frameSectionOffsets = std::move( otherFrame.m_frameSectionOffsets );
}

Frame::Frame( const Frame& otherFrame )
{
    m_frameWidth = otherFrame.m_frameWidth;
    m_frameHeight = otherFrame.m_frameHeight;

    m_buffer = std::make_unique< std::vector< std::vector< wchar_t > > >( *otherFrame.m_buffer );

    m_frameSectionDimensions = std::make_unique< std::array< Vec2I, static_cast< size_t >( FrameSection::MAX ) > >(
        *otherFrame.m_frameSectionDimensions );

    m_frameSectionOffsets = std::make_unique< std::array< Vec2I, static_cast< size_t >( FrameSection::MAX ) > >(
        *otherFrame.m_frameSectionOffsets );
}

Frame::~Frame()
{
}

bool Frame::Write( int x, int y, wchar_t dat, FrameSection section )
{
    ValidateSection( section );

    if ( Empty() )
        return false;
    if ( x < 0 || x >= m_frameWidth || y < 0 || y >= m_frameHeight )
        return false;

    if ( section == FrameSection::NONE )
    {
        ( *m_buffer )[ y ][ x ] = dat;
        return true;
    }

    x += ( *m_frameSectionOffsets )[ static_cast< size_t >( section ) ].x;
    y += ( *m_frameSectionOffsets )[ static_cast< size_t >( section ) ].y;

    Vec2I maxFrameDim = Vec2I{ x, y } + ( *m_frameSectionDimensions )[ static_cast< size_t >( section ) ];
    if ( x >= maxFrameDim.x || y >= maxFrameDim.y )
        return false;
    else if ( x < 0 || x >= m_frameWidth || y < 0 || y >= m_frameHeight )
        return false;

    ( *m_buffer )[ y ][ x ] = dat;
    return true;
}

bool Frame::Write( Vec2I point, wchar_t dat, FrameSection section )
{
    ValidateSection( section );
    return Write( point.x, point.y, dat, section );
}

wchar_t Frame::At( int x, int y ) const
{
    if ( x < 0 || x >= m_frameWidth || y < 0 || y >= m_frameHeight )
        return INVALID_CHAR;

    return ( *m_buffer )[ y ][ x ];
}

wchar_t Frame::At( Vec2I pos ) const
{
    return At( pos.x, pos.y );
}

void Frame::SetSection( FrameSection section, Vec2I offset, Vec2I dimension )
{
    ValidateSection( section );

    ( *m_frameSectionDimensions )[ static_cast< size_t >( section ) ] = dimension;
    ( *m_frameSectionOffsets )[ static_cast< size_t >( section ) ] = offset;
}

Vec2I Frame::GetSectionOffset( FrameSection section )
{
    return ( *m_frameSectionOffsets )[ static_cast< size_t >( section ) ];
}

Vec2I Frame::GetSectionDimension( FrameSection section )
{
    return ( *m_frameSectionDimensions )[ static_cast< size_t >( section ) ];
}

void Frame::ValidateSection( FrameSection section )
{
    assert( section != FrameSection::MAX && section != FrameSection::INVALID );
}

bool Frame::Empty() const
{
    return ( *m_buffer ).empty();
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
