//
// Created by Argyraspides on 8/23/25.
//

#ifndef DRAWUTILS_HPP
#define DRAWUTILS_HPP

#include "Frame.hpp"
struct Vec2I;
struct Sprite;
struct SpritePC;

namespace DrawUtils
{

static constexpr wchar_t TRANSPARENT_CHAR = '`';

void DrawLineVertical(
    int y1, int y2, int x, Frame& frame, wchar_t drawChar, Frame::Section section = Frame::Section::NONE );

void DrawLineHorizontal(
    int x1, int x2, int y, Frame& frame, wchar_t drawChar, Frame::Section section = Frame::Section::NONE );

void DrawLine( Vec2I p1, // Starting point
               Vec2I p2, // Ending point
               Frame& frame,
               wchar_t drawChar,
               Frame::Section section = Frame::Section::NONE );

void DrawPixel( Vec2I p, Frame& frame, wchar_t drawChar, Frame::Section section = Frame::Section::NONE );

void ClearFrame( Frame& frame, wchar_t clearChar, Frame::Section section = Frame::Section::NONE );

void ResetTerminalCursor();

void SetToSystemLocale();

void RenderFrame( Frame& frame );

void DrawBorder( Frame& frame, Frame::Section section = Frame::Section::NONE );

void DrawSetGreen();
void DrawSetWhite();
void DrawSetRed();

void DrawSprite( const Sprite& sprite,
                  Frame& frame,
                  wchar_t drawChar,
                  Vec2I offset = { 0, 0 },
                  float rotation = 0.0,
                  Frame::Section section = Frame::Section::NONE );

void RotateSprite( Sprite& sprite, int rotation );

Matf< 2, 2 > GetRotationMat( float rotation );

} // namespace DrawUtils

#endif // DRAWUTILS_HPP
