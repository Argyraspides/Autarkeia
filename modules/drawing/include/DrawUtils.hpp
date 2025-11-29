//
// Created by Argyraspides on 8/23/25.
//

#ifndef DRAWUTILS_HPP
#define DRAWUTILS_HPP

#include "Characters.hpp"
#include "Frame.hpp"
#include "Sprite.hpp"

namespace DrawUtils
{

void EnableEcho();

void DisableEcho();

void HideCursor();

void ShowCursor();

void DrawLineVertical(
    int y1, int y2, int x, Frame& frame, DrawChar drawChar, Frame::Section section = Frame::Section::NONE );

void DrawLineHorizontal(
    int x1, int x2, int y, Frame& frame, DrawChar drawChar, Frame::Section section = Frame::Section::NONE );

void DrawLine( Vec2I p1, // Starting point
               Vec2I p2, // Ending point
               Frame& frame,
               DrawChar drawChar,
               Frame::Section section = Frame::Section::NONE );

void DrawPixel( Vec2I p, Frame& frame, DrawChar drawChar, Frame::Section section = Frame::Section::NONE );

void ClearFrame( Frame& frame, DrawChar clearChar, Frame::Section section = Frame::Section::NONE );

void ResetTerminalCursor();

void SetToSystemLocale();

void RenderFrame( Frame& frame );

void DrawBorder( Frame& frame, Frame::Section section = Frame::Section::NONE );

void DrawSetColor( Color color );

void DrawSetGreen();

void DrawSetWhite();

void DrawSetRed();

void DrawSprite( const Sprite& sprite,
                 Frame& frame,
                 DrawChar drawChar,
                 Vec2I offset = { 0, 0 },
                 Frame::Section section = Frame::Section::NONE );

void RotateSprite( Sprite& sprite, int rotation );

Matf< 2, 2 > GetRotationMat( float rotation );

} // namespace DrawUtils

#endif // DRAWUTILS_HPP
