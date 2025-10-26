//
// Created by Argyraspides on 8/23/25.
//

#ifndef DRAWUTILS_HPP
#define DRAWUTILS_HPP

class Frame;
struct Vec2I;

namespace DrawUtils
{
void DrawLine( Vec2I p1, // Starting point
                      Vec2I p2, // Ending point
                      Frame& frameBuffer,
                      char drawChar );

void DrawLineVertical( int y1, int y2, int x, Frame& frame, char drawChar );
void DrawLineHorizontal( int x1, int x2, int y, Frame& frame, char drawChar );
void QuickDrawLine( Vec2I p1, // Starting point
                           Vec2I p2, // Ending point
                           Frame& frame,
                           char drawChar );

void DrawTriangle( Vec2I p1, Vec2I p2, Vec2I p3, Frame& frame, char drawChar );
void QuickDrawTriangle( Vec2I p1, Vec2I p2, Vec2I p3, Frame& frame, char drawChar );
void DrawPixel( Vec2I p, Frame& frame, char drawChar );

void Clear( Frame& frame, char clearChar );
void ClearScreen();
void Draw( Frame& frame );

} // namespace DrawUtils

#endif // DRAWUTILS_HPP
