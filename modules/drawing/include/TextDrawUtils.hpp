#pragma once

#include "Frame.hpp"
#include <string>

class Vec2I;
class Frame;

namespace DrawUtils
{
void DrawText( const std::string& txt,
               Vec2I dim,
               Frame& frame,
               char drawChar,
               int spacing = 2,
               FrameSection section = FrameSection::NONE );
}