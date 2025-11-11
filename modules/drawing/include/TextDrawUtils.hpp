#pragma once

#include "Frame.hpp"
#include <string>
#include "LetterGlyphs.hpp"
#include "Vec2I.hpp"
#include <cctype>
#include <span>

class Vec2I;
class Frame;

namespace DrawUtils
{

void DrawCharacter( std::span< const std::pair< CharBoxPosition, CharBoxPosition > > glyph,
                    Vec2I dim,
                    Vec2I offset,
                    Frame& frame,
                    wchar_t drawChar,
                    FrameSection section = FrameSection::NONE );

void DrawText( const std::string& txt,
               Vec2I dim,
               Frame& frame,
               wchar_t drawChar,
               int spacing = 2,
               FrameSection section = FrameSection::NONE );
}