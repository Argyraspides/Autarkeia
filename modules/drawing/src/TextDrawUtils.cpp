#include "TextDrawUtils.hpp"
#include "DrawUtils.hpp"
#include "Frame.hpp"
#include "LetterGlyphs.hpp"
#include "Vec2I.hpp"
#include <cctype>
#include <span>

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

    Vec2I CENTER = { dim.x / 2, dim.y / 2 };

    std::array< Vec2I, CharBoxPosition::MAX > realPositions = {
        { TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, TOP_MIDDLE, BOTTOM_MIDDLE, LEFT_MIDDLE, RIGHT_MIDDLE, CENTER } };

    for ( const std::pair< CharBoxPosition, CharBoxPosition >& line : glyph )
    {
        const Vec2I p1 = realPositions[ line.first ] + offset;
        const Vec2I p2 = realPositions[ line.second ] + offset;

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
        case '0':
            DrawCharacter( NUMBER_ZERO, dim, currOffset, frame, drawChar );
            break;
        case '1':
            DrawCharacter( NUMBER_ONE, dim, currOffset, frame, drawChar );
            break;
        case '2':
            DrawCharacter( NUMBER_TWO, dim, currOffset, frame, drawChar );
            break;
        case '3':
            DrawCharacter( NUMBER_THREE, dim, currOffset, frame, drawChar );
            break;
        case '4':
            DrawCharacter( NUMBER_FOUR, dim, currOffset, frame, drawChar );
            break;
        case '5':
            DrawCharacter( NUMBER_FIVE, dim, currOffset, frame, drawChar );
            break;
        case '6':
            DrawCharacter( NUMBER_SIX, dim, currOffset, frame, drawChar );
            break;
        case '7':
            DrawCharacter( NUMBER_SEVEN, dim, currOffset, frame, drawChar );
            break;
        case '8':
            DrawCharacter( NUMBER_EIGHT, dim, currOffset, frame, drawChar );
            break;
        case '9':
            DrawCharacter( NUMBER_NINE, dim, currOffset, frame, drawChar );
            break;
        }
        currOffset.x += ( dim.x + spacing );
    }
}

} // namespace DrawUtils