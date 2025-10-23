#pragma once
#include <array>

enum CharBoxPosition
{
    TOP_LEFT,
    TOP_RIGHT,

    BOTTOM_LEFT,
    BOTTOM_RIGHT,

    TOP_MIDDLE,
    BOTTOM_MIDDLE,

    LEFT_MIDDLE,
    RIGHT_MIDDLE,
};

const std::array< std::pair< CharBoxPosition, CharBoxPosition >, 4 > LETTER_A = { {
    { CharBoxPosition::BOTTOM_LEFT, CharBoxPosition::TOP_LEFT },
    { CharBoxPosition::BOTTOM_RIGHT, CharBoxPosition::TOP_RIGHT },
    { CharBoxPosition::TOP_LEFT, CharBoxPosition::TOP_RIGHT },
    { CharBoxPosition::LEFT_MIDDLE, CharBoxPosition::RIGHT_MIDDLE },
} };

const std::array< std::pair< CharBoxPosition, CharBoxPosition >, 6 > LETTER_B = { {
    { CharBoxPosition::BOTTOM_LEFT, CharBoxPosition::TOP_LEFT },
    { CharBoxPosition::TOP_LEFT, CharBoxPosition::TOP_RIGHT },
    { CharBoxPosition::TOP_RIGHT, CharBoxPosition::RIGHT_MIDDLE },
    { CharBoxPosition::LEFT_MIDDLE, CharBoxPosition::RIGHT_MIDDLE },
    { CharBoxPosition::RIGHT_MIDDLE, CharBoxPosition::BOTTOM_RIGHT },
    { CharBoxPosition::BOTTOM_RIGHT, CharBoxPosition::BOTTOM_LEFT },
} };

const std::array< std::pair< CharBoxPosition, CharBoxPosition >, 3 > LETTER_C = { {
    { CharBoxPosition::BOTTOM_LEFT, CharBoxPosition::TOP_LEFT },
    { CharBoxPosition::TOP_LEFT, CharBoxPosition::TOP_RIGHT },
    { CharBoxPosition::BOTTOM_LEFT, CharBoxPosition::BOTTOM_RIGHT },
} };

const std::array< std::pair< CharBoxPosition, CharBoxPosition >, 4 > LETTER_D = { {
    { CharBoxPosition::BOTTOM_LEFT, CharBoxPosition::TOP_LEFT },
    { CharBoxPosition::TOP_LEFT, CharBoxPosition::TOP_RIGHT },
    { CharBoxPosition::BOTTOM_LEFT, CharBoxPosition::BOTTOM_RIGHT },
    { CharBoxPosition::TOP_RIGHT, CharBoxPosition::BOTTOM_RIGHT },
} };

const std::array< std::pair< CharBoxPosition, CharBoxPosition >, 4 > LETTER_E = { {
    { CharBoxPosition::BOTTOM_LEFT, CharBoxPosition::TOP_LEFT },
    { CharBoxPosition::TOP_LEFT, CharBoxPosition::TOP_RIGHT },
    { CharBoxPosition::LEFT_MIDDLE, CharBoxPosition::RIGHT_MIDDLE },
    { CharBoxPosition::BOTTOM_LEFT, CharBoxPosition::BOTTOM_RIGHT },
} };

const std::array< std::pair< CharBoxPosition, CharBoxPosition >, 3 > LETTER_F = { {
    { CharBoxPosition::BOTTOM_LEFT, CharBoxPosition::TOP_LEFT },
    { CharBoxPosition::TOP_LEFT, CharBoxPosition::TOP_RIGHT },
    { CharBoxPosition::LEFT_MIDDLE, CharBoxPosition::RIGHT_MIDDLE },
} };

const std::array< std::pair< CharBoxPosition, CharBoxPosition >, 4 > LETTER_G = { {
    { CharBoxPosition::BOTTOM_LEFT, CharBoxPosition::TOP_LEFT },
    { CharBoxPosition::TOP_LEFT, CharBoxPosition::TOP_RIGHT },
    { CharBoxPosition::BOTTOM_LEFT, CharBoxPosition::BOTTOM_RIGHT },
    { CharBoxPosition::BOTTOM_RIGHT, CharBoxPosition::RIGHT_MIDDLE },
} };