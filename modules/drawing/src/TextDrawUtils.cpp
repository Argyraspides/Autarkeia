#include "TextDrawUtils.hpp"
#include "DrawUtils.hpp"
#include "Frame.hpp"
#include "Vec2I.hpp"
#include <array>
#include <utility>
#include <unordered_map>

enum CharBoxPosition
{
    TOP_LEFT,
    TOP_RIGHT,

    BOTTOM_LEFT,
    BOTTOM_RIGHT,

    TOP_MIDDLE,
    BOTTOM_MIDDLE,

    LEFT_MIDDLE,
    RIGHT_MIDDLE
};

static std::array< std::pair< CharBoxPosition, CharBoxPosition >, 4 > LETTER_A = { {
    { CharBoxPosition::BOTTOM_LEFT, CharBoxPosition::TOP_LEFT },
    { CharBoxPosition::BOTTOM_RIGHT, CharBoxPosition::TOP_RIGHT },
    { CharBoxPosition::BOTTOM_RIGHT, CharBoxPosition::TOP_RIGHT },
    { CharBoxPosition::BOTTOM_RIGHT, CharBoxPosition::TOP_RIGHT },
} };

namespace DrawUtils
{


void _DrawCharacter( const std::array< std::pair< CharBoxPosition, CharBoxPosition >, 4 >& glyph,
                     Vec2I dim,
                     Frame& frame,
                     const char& drawChar )
{
    Vec2I BOTTOM_LEFT = { 0, dim.y };
    Vec2I BOTTOM_RIGHT = { dim.x, dim.y };

    Vec2I TOP_LEFT = { 0, 0 };
    Vec2I TOP_RIGHT = { dim.x, 0 };

    Vec2I TOP_MIDDLE = { dim.x / 2, 0 };
    Vec2I BOTTOM_MIDDLE = { dim.x / 2, dim.y };

    Vec2I LEFT_MIDDLE = { 0, dim.y / 2 };
    Vec2I RIGHT_MIDDLE = { dim.x, dim.y / 2 };

    std::unordered_map< CharBoxPosition, Vec2I > charBoxToVec;
    charBoxToVec[CharBoxPosition::BOTTOM_LEFT] = BOTTOM_LEFT; 
    charBoxToVec[CharBoxPosition::BOTTOM_RIGHT] = BOTTOM_RIGHT; 

    charBoxToVec[CharBoxPosition::TOP_LEFT] = TOP_LEFT; 
    charBoxToVec[CharBoxPosition::TOP_RIGHT] = TOP_RIGHT; 

    charBoxToVec[CharBoxPosition::TOP_MIDDLE] = TOP_MIDDLE; 
    charBoxToVec[CharBoxPosition::BOTTOM_MIDDLE] = BOTTOM_MIDDLE; 
    
    charBoxToVec[CharBoxPosition::LEFT_MIDDLE] = LEFT_MIDDLE; 
    charBoxToVec[CharBoxPosition::RIGHT_MIDDLE] = RIGHT_MIDDLE; 

    for ( const std::pair< CharBoxPosition, CharBoxPosition >& line : glyph )
    {
        const Vec2I& p1 = charBoxToVec.at(line.first);
        const Vec2I& p2 = charBoxToVec.at(line.second);
        DrawUtils::DrawLine(p1, p2, frame, drawChar);
    }
}

void DrawCharacter( const char& ch, Vec2I dim, Frame& frame, const char& drawChar )
{
    switch ( ch )
    {
    case 'a':
    case 'A': {
        _DrawCharacter( LETTER_A, dim, frame, drawChar );
    }
    }
}

void DrawText( const std::string& txt, const Vec2I& dim, Frame& frame, const char& drawChar )
{
    for( const char& c : txt )
    {
        DrawCharacter(c, dim, frame, drawChar );
    }
}

} // namespace DrawUtil