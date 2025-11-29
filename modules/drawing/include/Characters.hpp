#pragma once

#include "Color.hpp"
#include <string>

inline constexpr wchar_t INVALID_CHAR = L'\0';

inline constexpr wchar_t SHADE_0 = L' '; // 0% (empty)
inline constexpr wchar_t SHADE_1 = L'░'; // 25% (light shade)
inline constexpr wchar_t SHADE_2 = L'▒'; // 50% (medium shade)
inline constexpr wchar_t SHADE_3 = L'▓'; // 75% (dark shade)
inline constexpr wchar_t SHADE_4 = L'█'; // 100% (full block)

inline constexpr wchar_t BLOCK_LEFT_HALF = L'▌';
inline constexpr wchar_t BLOCK_RIGHT_HALF = L'▐';
inline constexpr wchar_t BLOCK_LEFT_3_4 = L'▊';
inline constexpr wchar_t BLOCK_LEFT_5_8 = L'▋';
inline constexpr wchar_t BLOCK_LEFT_1_2 = L'▌';
inline constexpr wchar_t BLOCK_LEFT_3_8 = L'▍';
inline constexpr wchar_t BLOCK_LEFT_1_4 = L'▎';
inline constexpr wchar_t BLOCK_LEFT_1_8 = L'▏';

inline constexpr wchar_t BLOCK_UPPER_HALF = L'▀';
inline constexpr wchar_t BLOCK_LOWER_HALF = L'▄';
inline constexpr wchar_t BLOCK_UPPER_3_4 = L'▛';
inline constexpr wchar_t BLOCK_UPPER_5_8 = L'▜';
inline constexpr wchar_t BLOCK_UPPER_3_8 = L'▔';
inline constexpr wchar_t BLOCK_UPPER_1_4 = L'▀';
inline constexpr wchar_t BLOCK_LOWER_1_4 = L'▁';
inline constexpr wchar_t BLOCK_LOWER_3_8 = L'▂';
inline constexpr wchar_t BLOCK_LOWER_1_2 = L'▃';
inline constexpr wchar_t BLOCK_LOWER_5_8 = L'▄';
inline constexpr wchar_t BLOCK_LOWER_3_4 = L'▅';
inline constexpr wchar_t BLOCK_LOWER_7_8 = L'▆';

inline constexpr wchar_t QUADRANT_UPPER_LEFT = L'▘';
inline constexpr wchar_t QUADRANT_UPPER_RIGHT = L'▝';
inline constexpr wchar_t QUADRANT_LOWER_LEFT = L'▖';
inline constexpr wchar_t QUADRANT_LOWER_RIGHT = L'▗';
inline constexpr wchar_t QUADRANT_UPPER_LEFT_LOWER_RIGHT = L'▚';
inline constexpr wchar_t QUADRANT_UPPER_RIGHT_LOWER_LEFT = L'▞';

inline constexpr wchar_t HORIZONTAL_LINE = L'─';
inline constexpr wchar_t VERTICAL_LINE = L'│';
inline constexpr wchar_t TOP_LEFT_CORNER = L'┌';
inline constexpr wchar_t TOP_RIGHT_CORNER = L'┐';
inline constexpr wchar_t BOTTOM_LEFT_CORNER = L'└';
inline constexpr wchar_t BOTTOM_RIGHT_CORNER = L'┘';

inline constexpr wchar_t DIAGONAL_UPPER_LEFT_TO_LOWER_RIGHT = L'╲';
inline constexpr wchar_t DIAGONAL_UPPER_RIGHT_TO_LOWER_LEFT = L'╱';
inline constexpr wchar_t DIAGONAL_CROSS = L'╳';

inline constexpr wchar_t STIPPLE_LIGHT = L'·';
inline constexpr wchar_t STIPPLE_MEDIUM = L'∴';
inline constexpr wchar_t STIPPLE_HEAVY = L'⁘';

inline constexpr std::string ANSI_GREEN = "\033[32m";
inline constexpr std::string ANSI_WHITE = "\033[37m";
inline constexpr std::string ANSI_RED = "\033[31m";
inline constexpr std::string ANSI_HIDE_CURSOR = "\033[?25l";
inline constexpr std::string ANSI_SHOW_CURSOR = "\033[?25h";

// TODO::REFACTOR::ARGYRASPIDES() { Move to a separate cpp? }
struct DrawChar
{
    DrawChar()
        : color( Color::WHITE ){};

    DrawChar( wchar_t drawChar )
        : drawChar( drawChar ),
          color( Color::WHITE ){};

    DrawChar( wchar_t drawChar, Color color )
        : drawChar( drawChar ),
          color( color ){};

    wchar_t drawChar;
    Color color;
};