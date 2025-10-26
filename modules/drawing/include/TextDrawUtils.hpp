#pragma once

#include <string>

class Vec2I;
class Frame;

namespace DrawUtils
{
void DrawText( const std::string& txt, Vec2I dim, Frame& frame, char drawChar, int spacing = 3 );
}