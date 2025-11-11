//
// Created by Argyraspides on 8/23/25.
//

#ifndef DRAWUTILS_HPP
#define DRAWUTILS_HPP

#include "Frame.hpp"
struct Vec2I;
struct Sprite;

namespace DrawUtils
{

static constexpr wchar_t TRANSPARENT_CHAR = '`';

void DrawLine( Vec2I p1, // Starting point
               Vec2I p2, // Ending point
               Frame& frameBuffer,
               wchar_t drawChar,
               FrameSection section = FrameSection::NONE );

void DrawLineVertical( int y1, int y2, int x, Frame& frame, wchar_t drawChar, FrameSection section = FrameSection::NONE );

void DrawLineHorizontal(
    int x1, int x2, int y, Frame& frame, wchar_t drawChar, FrameSection section = FrameSection::NONE );

void DrawLineOnFrame( Vec2I p1, // Starting point
                    Vec2I p2, // Ending point
                    Frame& frame,
                    wchar_t drawChar,
                    FrameSection section = FrameSection::NONE );

void DrawTriangleOnFrame(
    Vec2I p1, Vec2I p2, Vec2I p3, Frame& frame, wchar_t drawChar, FrameSection section = FrameSection::NONE );

void DrawPixelOnFrame( Vec2I p, Frame& frame, wchar_t drawChar, FrameSection section = FrameSection::NONE );

void ClearFrame( Frame& frame, wchar_t clearChar, FrameSection section = FrameSection::NONE );

void ResetTerminalCursor();

void SetToSystemLocale();

void DrawFrame( Frame& frame );

void DrawBorderOnFrame( Frame& frame, FrameSection section = FrameSection::NONE );

void DrawSpriteOnFrame( const Sprite& sprite,
                 Frame& frame,
                 Vec2I offset = { 0, 0 },
                 float rotation = 0.0,
                 FrameSection section = FrameSection::NONE );

// Rotation in degrees not radians
Frame&& RotateSprite( const Sprite& sprite, float rotation = 0.0f );

Matf< 2, 2 > GetRotationMat( float rotation );

} // namespace DrawUtils

#endif // DRAWUTILS_HPP
