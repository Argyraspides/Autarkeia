#include "TextDrawUtils.hpp"
#include "DrawUtils.hpp"
#include "Frame.hpp"

namespace DrawUtils
{
void DrawCharacter( std::span< const std::pair< CharBoxPosition, CharBoxPosition > > glyph,
                    Vec2I dim,
                    Vec2I offset,
                    Frame& frame,
                    wchar_t drawChar,
                    FrameSection section )
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

    std::array< Vec2I, static_cast< size_t >( CharBoxPosition::MAX ) > realPositions = {
        { TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, TOP_MIDDLE, BOTTOM_MIDDLE, LEFT_MIDDLE, RIGHT_MIDDLE, CENTER } };

    for ( const std::pair< CharBoxPosition, CharBoxPosition >& line : glyph )
    {
        const Vec2I p1 = realPositions[ static_cast< size_t >( line.first ) ] + offset;
        const Vec2I p2 = realPositions[ static_cast< size_t >( line.second ) ] + offset;

        DrawUtils::DrawLineOnFrame( p1, p2, frame, drawChar, section );
    }
}

void DrawText( const std::string& txt, Vec2I dim, Frame& frame, wchar_t drawChar, int spacing, FrameSection section )
{

    Vec2I currOffset = { 0, 0 };
    for ( const wchar_t c : txt )
    {
        switch ( c )
        {
        case '0':
            DrawCharacter( NUMBER_ZERO, dim, currOffset, frame, drawChar, section );
            break;
        case '1':
            DrawCharacter( NUMBER_ONE, dim, currOffset, frame, drawChar, section );
            break;
        case '2':
            DrawCharacter( NUMBER_TWO, dim, currOffset, frame, drawChar, section );
            break;
        case '3':
            DrawCharacter( NUMBER_THREE, dim, currOffset, frame, drawChar, section );
            break;
        case '4':
            DrawCharacter( NUMBER_FOUR, dim, currOffset, frame, drawChar, section );
            break;
        case '5':
            DrawCharacter( NUMBER_FIVE, dim, currOffset, frame, drawChar, section );
            break;
        case '6':
            DrawCharacter( NUMBER_SIX, dim, currOffset, frame, drawChar, section );
            break;
        case '7':
            DrawCharacter( NUMBER_SEVEN, dim, currOffset, frame, drawChar, section );
            break;
        case '8':
            DrawCharacter( NUMBER_EIGHT, dim, currOffset, frame, drawChar, section );
            break;
        case '9':
            DrawCharacter( NUMBER_NINE, dim, currOffset, frame, drawChar, section );
            break;
        }
        currOffset.x += ( dim.x + spacing );
    }
}

} // namespace DrawUtils