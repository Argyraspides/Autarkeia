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

Frame::Frame( size_t width, size_t height )
    : m_frameWidth( width ),
      m_frameHeight( height )
{

    m_buffer = std::vector< std::vector< DrawChar > >( height, std::vector< DrawChar >( width ) );

    const Vec2I INVALID_POINT = { std::numeric_limits< int >::quiet_NaN(), std::numeric_limits< int >::quiet_NaN() };

    m_frameSectionOffsets = std::array< Vec2I, static_cast< size_t >( Frame::Section::MAX ) >();
    for ( Vec2I& v : m_frameSectionOffsets )
        v = INVALID_POINT;

    m_frameSectionDimensions = std::array< Vec2I, static_cast< size_t >( Frame::Section::MAX ) >();
    for ( Vec2I& v : m_frameSectionDimensions )
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

    m_buffer = std::vector< std::vector< DrawChar > >( otherFrame.m_buffer );

    m_frameSectionDimensions =
        std::array< Vec2I, static_cast< size_t >( Frame::Section::MAX ) >( otherFrame.m_frameSectionDimensions );

    m_frameSectionOffsets =
        std::array< Vec2I, static_cast< size_t >( Frame::Section::MAX ) >( otherFrame.m_frameSectionOffsets );
}

Frame::~Frame()
{
}

bool Frame::Write( int x, int y, DrawChar  dat, Frame::Section section )
{
    // TODO::THINKABOUT::ARGYRASPIDES() { Why do you have an assertion for checking valid sections, but then suddenly
    // you just return false if the pixel itself is out of bounds? }
    ValidateSection( section );

    if ( Empty() )
        return false;
    if ( !InFrame( { x, y } ) )
        return false;

    if ( section == Frame::Section::NONE )
    {
        m_buffer[ y ][ x ] = dat;
        return true;
    }

    x += ( m_frameSectionOffsets )[ static_cast< size_t >( section ) ].x;
    y += ( m_frameSectionOffsets )[ static_cast< size_t >( section ) ].y;

    Vec2I maxFrameDim = Vec2I{ x, y } + ( m_frameSectionDimensions )[ static_cast< size_t >( section ) ];
    if ( !InFrame( { x, y } ) )
        return false;

    m_buffer[ y ][ x ] = dat;
    return true;
}

bool Frame::Write( Vec2I point, DrawChar dat, Frame::Section section )
{
    ValidateSection( section );
    return Write( point.x, point.y, dat, section );
}

wchar_t Frame::CharAt( int x, int y ) const
{
    if ( x < 0 || x >= m_frameWidth || y < 0 || y >= m_frameHeight )
        return INVALID_CHAR;

    return m_buffer[ y ][ x ].drawChar;
}

wchar_t Frame::CharAt( Vec2I pos ) const
{
    return CharAt( pos.x, pos.y );
}

DrawChar Frame::At( int x, int y ) const
{
    if ( x < 0 || x >= m_frameWidth || y < 0 || y >= m_frameHeight )
        return INVALID_CHAR;

    return m_buffer[ y ][ x ];
}

DrawChar Frame::At( Vec2I pos ) const
{
    return At( pos.x, pos.y );
}

void Frame::SetSection( Frame::Section section, Vec2I offset, Vec2I dimension )
{
    ValidateSection( section );

    m_frameSectionDimensions[ static_cast< size_t >( section ) ] = dimension;
    m_frameSectionOffsets[ static_cast< size_t >( section ) ] = offset;
}

Vec2I Frame::GetSectionOffset( Frame::Section section )
{
    return m_frameSectionOffsets[ static_cast< size_t >( section ) ];
}

Vec2I Frame::GetSectionDimension( Frame::Section section )
{
    return m_frameSectionDimensions[ static_cast< size_t >( section ) ];
}

bool Frame::InFrame( Vec2I screenPos )
{
    bool outOfBounds =
        screenPos.x < 0 || screenPos.x >= m_frameWidth || screenPos.y < 0 || screenPos.y >= m_frameHeight;
    return !outOfBounds;
}

void Frame::ValidateSection( Frame::Section section )
{
    assert( section != Frame::Section::MAX && section != Frame::Section::INVALID );
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
