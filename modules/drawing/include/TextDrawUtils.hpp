#pragma once

#include <string>

class Vec2I;
class Frame;

namespace DrawUtils
{
void DrawText( const std::string& txt, const Vec2I& dim, Frame& frame, const char& drawChar );
}