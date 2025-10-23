#include "TextDrawUtils.hpp"
#include "DrawUtils.hpp"
#include "Frame.hpp"
#include "LetterGlyphs.hpp"
#include "Vec2I.hpp"
#include <span>
#include <unordered_map>

namespace DrawUtils
{

void DrawCharacter( std::span< const std::pair< CharBoxPosition, CharBoxPosition > > glyph,
                    Vec2I dim,
                    Vec2I offset,
                    Frame& frame,
                    char drawChar )
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
    charBoxToVec[ CharBoxPosition::BOTTOM_LEFT ] = BOTTOM_LEFT;
    charBoxToVec[ CharBoxPosition::BOTTOM_RIGHT ] = BOTTOM_RIGHT;

    charBoxToVec[ CharBoxPosition::TOP_LEFT ] = TOP_LEFT;
    charBoxToVec[ CharBoxPosition::TOP_RIGHT ] = TOP_RIGHT;

    charBoxToVec[ CharBoxPosition::TOP_MIDDLE ] = TOP_MIDDLE;
    charBoxToVec[ CharBoxPosition::BOTTOM_MIDDLE ] = BOTTOM_MIDDLE;

    charBoxToVec[ CharBoxPosition::LEFT_MIDDLE ] = LEFT_MIDDLE;
    charBoxToVec[ CharBoxPosition::RIGHT_MIDDLE ] = RIGHT_MIDDLE;

    for ( const std::pair< CharBoxPosition, CharBoxPosition >& line : glyph )
    {
        const Vec2I p1 = charBoxToVec.at( line.first ) + offset;
        const Vec2I p2 = charBoxToVec.at( line.second ) + offset;

        DrawUtils::QuickDrawLine( p1, p2, frame, drawChar );
    }
}

void DrawText( const std::string& txt, Vec2I dim, Frame& frame, char drawChar, int spacing )
{
    Vec2I currOffset = { 0, 0 };
    for ( const char c : txt )
    {
        switch ( c )
        {
        case 'A':
            DrawCharacter( LETTER_A, dim, currOffset, frame, drawChar );
            break;
        case 'B':
            DrawCharacter( LETTER_B, dim, currOffset, frame, drawChar );
            break;
        case 'C':
            DrawCharacter( LETTER_C, dim, currOffset, frame, drawChar );
            break;
        case 'D':
            DrawCharacter( LETTER_D, dim, currOffset, frame, drawChar );
            break;
        case 'E':
            DrawCharacter( LETTER_E, dim, currOffset, frame, drawChar );
            break;
        case 'F':
            DrawCharacter( LETTER_F, dim, currOffset, frame, drawChar );
            break;
        case 'G':
            DrawCharacter( LETTER_G, dim, currOffset, frame, drawChar );
            break;
        }
        currOffset.x += ( dim.x + spacing );
    }
}

} // namespace DrawUtils