//
// Created by Argyraspides on 8/23/25.
//

#ifndef DRAWUTILS_HPP
#define DRAWUTILS_HPP

#include "Frame.hpp"
class Frame;
struct Vec2I;

namespace DrawUtils
{
void DrawLine( Vec2I p1, // Starting point
               Vec2I p2, // Ending point
               Frame& frameBuffer,
               char drawChar,
               FrameSection section = FrameSection::NONE );

void DrawLineVertical( int y1, int y2, int x, Frame& frame, char drawChar, FrameSection section = FrameSection::NONE );
void DrawLineHorizontal(
    int x1, int x2, int y, Frame& frame, char drawChar, FrameSection section = FrameSection::NONE );
void QuickDrawLine( Vec2I p1, // Starting point
                    Vec2I p2, // Ending point
                    Frame& frame,
                    char drawChar,
                    FrameSection section = FrameSection::NONE );

void DrawTriangle(
    Vec2I p1, Vec2I p2, Vec2I p3, Frame& frame, char drawChar, FrameSection section = FrameSection::NONE );
void QuickDrawTriangle(
    Vec2I p1, Vec2I p2, Vec2I p3, Frame& frame, char drawChar, FrameSection section = FrameSection::NONE );
void DrawPixel( Vec2I p, Frame& frame, char drawChar, FrameSection section = FrameSection::NONE );

void Clear( Frame& frame, char clearChar, FrameSection section = FrameSection::NONE );
void ResetTerminalCursor();
void Draw( Frame& frame );

} // namespace DrawUtils

#endif // DRAWUTILS_HPP
