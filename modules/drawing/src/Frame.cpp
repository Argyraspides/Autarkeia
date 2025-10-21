//
// Created by Argyraspides on 9/7/25.
//

#include "Frame.hpp"
#include "Vec2I.hpp"
#include <stdexcept>
#define DEFAULT_INIT_CHAR '.'

Frame::Frame( int width, int height )
    : m_frameWidth( width ),
      m_frameHeight( height )
{
    m_buffer = std::string( ( width * height ) + height, DEFAULT_INIT_CHAR );

    for ( int i = width; i < m_buffer.size(); i += ( width + 1 ) )
        m_buffer[ i ] = '\n';
}

Frame::~Frame()
{
}

bool Frame::Write( const int& x, const int& y, const char& dat )
{
    if ( Empty() )
        return false;
    if ( x < 0 || x >= m_frameWidth || y < 0 || y >= m_frameHeight )
        return false;

    // m_frameWidth + 1 because the end of each row is a newline that we forbid writing to
    m_buffer[ y * ( m_frameWidth + 1 ) + x ] = dat;
    return true;
}

bool Frame::Write( const Vec2I& point, const char& dat )
{
    return Write(point.x, point.y, dat);
}

char Frame::At( const int& x, const int& y ) const
{
    if ( x < 0 || x >= m_frameWidth || y < 0 || y >= m_frameHeight )
        throw std::out_of_range( "Cannot access (x,y) coordinate -- out of bounds" );

    // m_frameWidth + 1 because the end of each row is a newline that we forbid reading from
    return m_buffer[ y * ( m_frameWidth + 1 ) + x ];
}

std::string& Frame::Buffer()
{
    return m_buffer;
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
