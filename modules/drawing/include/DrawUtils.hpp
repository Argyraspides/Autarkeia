//
// Created by Argyraspides on 8/23/25.
//

#ifndef DRAWUTILS_HPP
#define DRAWUTILS_HPP

class Frame;
struct Vec2I;

namespace DrawUtils
{
void DrawLine( const Vec2I& p1, // Starting point
                      const Vec2I& p2, // Ending point
                      Frame& frameBuffer,
                      const char& drawChar );

void DrawLineVertical( int y1, int y2, int x, Frame& frame, const char& drawChar );
void DrawLineHorizontal( int x1, int x2, int y, Frame& frame, const char& drawChar );
void QuickDrawLine( const Vec2I& p1, // Starting point
                           const Vec2I& p2, // Ending point
                           Frame& frame,
                           const char& drawChar );

void DrawTriangle( const Vec2I& p1, const Vec2I& p2, const Vec2I& p3, Frame& frame, const char& drawChar );
void QuickDrawTriangle( const Vec2I& p1, const Vec2I& p2, const Vec2I& p3, Frame& frame, const char& drawChar );
void DrawPixel( const Vec2I& p, Frame& frame, const char& drawChar );

void Clear( Frame& frame, const char& clearChar );
void ClearScreen();
void Draw( Frame& frame );

} // namespace DrawUtils

#endif // DRAWUTILS_HPP
