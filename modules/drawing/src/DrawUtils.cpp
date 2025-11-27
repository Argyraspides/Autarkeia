//
// Created by gaugamela on 10/18/25.
//
#include "DrawUtils.hpp"
#include "Characters.hpp"
#include "Frame.hpp"
#include "Sprite.hpp"
#include "Vec2I.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <locale>
#include <string>
#include <unistd.h>


namespace DrawUtils
{

void DrawLineVertical( int y1, int y2, int x, Frame& frame, wchar_t drawChar, Frame::Section section )
{
    if ( y1 > y2 )
        std::swap( y1, y2 );

    while ( y1 <= y2 && frame.Write( x, y1++, drawChar, section ) )
        ;
}

void DrawLineHorizontal( int x1, int x2, int y, Frame& frame, wchar_t drawChar, Frame::Section section )
{

    if ( x1 > x2 )
        std::swap( x1, x2 );

    while ( x1 <= x2 && frame.Write( x1++, y, drawChar, section ) )
        ;
}

void DrawLine( Vec2I p1, // Starting point
               Vec2I p2, // Ending point
               Frame& frame,
               wchar_t drawChar,
               Frame::Section section )
{

    if ( p1.x == p2.x )
    {
        DrawLineVertical( p1.y, p2.y, p1.x, frame, drawChar, section );
        return;
    }

    if ( p1.y == p2.y )
    {
        DrawLineHorizontal( p1.x, p2.x, p1.y, frame, drawChar, section );
        return;
    }

    int dx = p2.x - p1.x;
    int dxPolarity = dx < 0 ? -1 : 1;

    int dy = p2.y - p1.y;
    int dyPolarity = dy < 0 ? -1 : 1;

    int dist = 0;

    if ( abs( dx ) >= abs( dy ) )
    {
        int it = abs( dx );
        Vec2I currPt = p1;
        for ( int i = 0; i <= it; i++ )
        {
            if ( dist < 0 )
            {
                currPt.y += dyPolarity;
                dist += dx * dxPolarity;
            }

            if ( !frame.Write( currPt.x, currPt.y, drawChar ) )
                break;

            currPt.x += dxPolarity;
            dist += -dy * dyPolarity;
        }
    }
    else
    {
        int it = abs( dy );
        Vec2I currPt = p1;
        for ( int i = 0; i <= it; i++ )
        {
            if ( dist > 0 )
            {
                currPt.x += dxPolarity;
                dist += -dy * dyPolarity;
            }

            if ( !frame.Write( currPt.x, currPt.y, drawChar ) )
                break;

            currPt.y += dyPolarity;
            dist += dx * dxPolarity;
        }
    }
}

void DrawPixel( Vec2I p, Frame& frame, wchar_t drawChar, Frame::Section section )
{
    frame.Write( p.x, p.y, drawChar, section );
}

void ClearFrame( Frame& frame, wchar_t clearChar, Frame::Section section )
{
    for ( int y = 0; y < frame.Height(); y++ )
        for ( int x = 0; x < frame.Width(); x++ )
            frame.Write( x, y, clearChar, section );
}

void ResetTerminalCursor()
{
    write( STDOUT_FILENO, "\33[H", 3 );
}

void SetToSystemLocale()
{
    std::locale::global( std::locale( "" ) );
    std::wcout.imbue( std::locale() );
}

void RenderFrame( Frame& frame )
{
    for ( int y = 0; y < frame.Height(); y++ )
    {
        for ( int x = 0; x < frame.Width(); x++ )
        {
            std::wcout << frame.At( x, y );
        }
        std::wcout << "\n";
    }
}

void DrawBorder( Frame& frame, Frame::Section section )
{
    Vec2I startIdx, dimension;
    if ( section == Frame::Section::NONE )
    {
        startIdx = { 0, 0 };
        dimension = { frame.Width(), frame.Height() };
    }
    else
    {
        startIdx = frame.GetSectionOffset( section );
        dimension = frame.GetSectionDimension( section );
    }
    Vec2I endIdx = startIdx + dimension;

    // Top
    frame.Write( startIdx.x, startIdx.y, TOP_LEFT_CORNER );
    for ( int i = startIdx.x + 1; i < endIdx.x - 1; i++ )
        frame.Write( i, startIdx.y, HORIZONTAL_LINE );

    frame.Write( endIdx.x - 1, startIdx.y, TOP_RIGHT_CORNER );

    // Sides
    for ( int i = startIdx.y + 1; i < endIdx.y - 1; i++ )
    {
        frame.Write( startIdx.x, i, VERTICAL_LINE );
        frame.Write( endIdx.x - 1, i, VERTICAL_LINE );
    }

    // Bottom
    frame.Write( startIdx.x, endIdx.y - 1, BOTTOM_LEFT_CORNER );
    for ( int i = startIdx.x + 1; i < endIdx.x; i++ )
        frame.Write( i, endIdx.y - 1, HORIZONTAL_LINE );

    frame.Write( endIdx.x - 1, endIdx.y - 1, BOTTOM_RIGHT_CORNER );
}

void DrawSetGreen()
{
    const std::string ANSI_GREEN = "\033[32m";
    std::wcout << ANSI_GREEN.c_str();
}

void DrawSetWhite()
{
    const std::string ANSI_WHITE = "\033[37m";
    std::wcout << ANSI_WHITE.c_str();
}

void DrawSetRed()
{
    static std::string ANSI_RED = "\033[31m";
    std::wcout << ANSI_RED .c_str();
}

void DrawSprite(
    const Sprite& sprite, Frame& frame, wchar_t drawChar, Vec2I offset, float rotation, Frame::Section section )
{
    const std::vector< Vec2I >& points = sprite.GetPointCloud();
    for ( int i = 0; i < points.size() - 1; i++ )
        DrawLine( points[ i ] + offset, points[ i + 1 ] + offset, frame, drawChar, section );
    DrawLine( points.front() + offset, points.back() + offset, frame, drawChar, section );
}

// I don't really like this coz it assumes the characters are gonna be like the shading ones
// zzz
wchar_t GetAverageShade( wchar_t s1, wchar_t s2, wchar_t s3, wchar_t s4 )
{
    wchar_t surroundingChars[ 4 ] = { s1, s2, s3, s4 };
    wchar_t shadeMap[ 5 ] = { SHADE_0, SHADE_1, SHADE_2, SHADE_3, SHADE_4 };
    int avg = 0;

    for ( int i = 0; i < 4; i++ )
    {
        switch ( surroundingChars[ i ] )
        {
        case INVALID_CHAR:
            break;
        case SHADE_0:
            avg++;
            break;
        case SHADE_1:
            avg += 2;
            break;
        case SHADE_2:
            avg += 3;
            break;
        case SHADE_3:
            avg += 4;
            break;
        case SHADE_4:
            avg += 5;
            break;
        default:
            assert( false && "GetAverageShade() MUST be called with a proper shading character!" );
        }
    }

    avg /= 5;

    return shadeMap[ avg ];
}

void RotateSprite( Sprite& sprite, int rotation )
{
    Matf< 2, 2 > rotMat = GetRotationMat( rotation );
    const std::vector< Vec2I >& spritePoints = sprite.GetBasePointCloud();

    for ( size_t i = 0; i < spritePoints.size(); i++ )
    {
        Vec2I transformedPt = spritePoints[ i ];
        Vec2I rotatedPt = ( transformedPt * rotMat );
        sprite.ChangePoint( i, rotatedPt );
    }
}

Matf< 2, 2 > GetRotationMat( float rotation )
{
    float rotRad = rotation * ( M_PI / 180.0f );

    Matf< 2, 2 > rotMatrix;
    rotMatrix[ 0 ][ 0 ] = std::cos( rotRad );
    rotMatrix[ 0 ][ 1 ] = -std::sin( rotRad );
    rotMatrix[ 1 ][ 0 ] = std::sin( rotRad );
    rotMatrix[ 1 ][ 1 ] = std::cos( rotRad );

    return rotMatrix;
}

} // namespace DrawUtils