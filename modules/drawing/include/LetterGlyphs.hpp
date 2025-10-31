#pragma once
#include <array>

enum class CharBoxPosition
{
    TOP_LEFT = 0,
    TOP_RIGHT,

    BOTTOM_LEFT,
    BOTTOM_RIGHT,

    TOP_MIDDLE,
    BOTTOM_MIDDLE,

    LEFT_MIDDLE,
    RIGHT_MIDDLE,

    CENTER,

    MAX
};

const std::array< std::pair< CharBoxPosition, CharBoxPosition >, 4 > NUMBER_ZERO = {
    { { CharBoxPosition::TOP_LEFT, CharBoxPosition::TOP_RIGHT },
      { CharBoxPosition::TOP_RIGHT, CharBoxPosition::BOTTOM_RIGHT },
      { CharBoxPosition::BOTTOM_RIGHT, CharBoxPosition::BOTTOM_LEFT },
      { CharBoxPosition::BOTTOM_LEFT, CharBoxPosition::TOP_LEFT } } };

const std::array< std::pair< CharBoxPosition, CharBoxPosition >, 3 > NUMBER_ONE = {
    { { CharBoxPosition::LEFT_MIDDLE, CharBoxPosition::TOP_MIDDLE },
      { CharBoxPosition::TOP_MIDDLE, CharBoxPosition::BOTTOM_MIDDLE },
      { CharBoxPosition::BOTTOM_LEFT, CharBoxPosition::BOTTOM_RIGHT } } };

const std::array< std::pair< CharBoxPosition, CharBoxPosition >, 5 > NUMBER_TWO = {
    { { CharBoxPosition::TOP_LEFT, CharBoxPosition::TOP_RIGHT },
      { CharBoxPosition::TOP_RIGHT, CharBoxPosition::RIGHT_MIDDLE },
      { CharBoxPosition::RIGHT_MIDDLE, CharBoxPosition::LEFT_MIDDLE },
      { CharBoxPosition::LEFT_MIDDLE, CharBoxPosition::BOTTOM_LEFT },
      { CharBoxPosition::BOTTOM_LEFT, CharBoxPosition::BOTTOM_RIGHT }

    } };

const std::array< std::pair< CharBoxPosition, CharBoxPosition >, 5 > NUMBER_THREE = {
    { { CharBoxPosition::TOP_LEFT, CharBoxPosition::TOP_RIGHT },
      { CharBoxPosition::TOP_RIGHT, CharBoxPosition::RIGHT_MIDDLE },
      { CharBoxPosition::RIGHT_MIDDLE, CharBoxPosition::CENTER },
      { CharBoxPosition::RIGHT_MIDDLE, CharBoxPosition::BOTTOM_RIGHT },
      { CharBoxPosition::BOTTOM_RIGHT, CharBoxPosition::BOTTOM_LEFT } } };

const std::array< std::pair< CharBoxPosition, CharBoxPosition >, 3 > NUMBER_FOUR = {
    { { CharBoxPosition::TOP_LEFT, CharBoxPosition::LEFT_MIDDLE },
      { CharBoxPosition::LEFT_MIDDLE, CharBoxPosition::RIGHT_MIDDLE },
      { CharBoxPosition::TOP_RIGHT, CharBoxPosition::BOTTOM_RIGHT } } };

const std::array< std::pair< CharBoxPosition, CharBoxPosition >, 5 > NUMBER_FIVE = {
    { { CharBoxPosition::TOP_RIGHT, CharBoxPosition::TOP_LEFT },
      { CharBoxPosition::TOP_LEFT, CharBoxPosition::LEFT_MIDDLE },
      { CharBoxPosition::LEFT_MIDDLE, CharBoxPosition::RIGHT_MIDDLE },
      { CharBoxPosition::RIGHT_MIDDLE, CharBoxPosition::BOTTOM_RIGHT },
      { CharBoxPosition::BOTTOM_RIGHT, CharBoxPosition::BOTTOM_LEFT }

    } };

const std::array< std::pair< CharBoxPosition, CharBoxPosition >, 5 > NUMBER_SIX = {
    { { CharBoxPosition::TOP_RIGHT, CharBoxPosition::TOP_LEFT },
      { CharBoxPosition::TOP_LEFT, CharBoxPosition::BOTTOM_LEFT },
      { CharBoxPosition::BOTTOM_LEFT, CharBoxPosition::BOTTOM_RIGHT },
      { CharBoxPosition::BOTTOM_RIGHT, CharBoxPosition::RIGHT_MIDDLE },
      { CharBoxPosition::RIGHT_MIDDLE, CharBoxPosition::LEFT_MIDDLE }

    } };

const std::array< std::pair< CharBoxPosition, CharBoxPosition >, 2 > NUMBER_SEVEN = {
    { { CharBoxPosition::TOP_LEFT, CharBoxPosition::TOP_RIGHT },
      { CharBoxPosition::TOP_RIGHT, CharBoxPosition::BOTTOM_RIGHT } } };

const std::array< std::pair< CharBoxPosition, CharBoxPosition >, 5 > NUMBER_EIGHT = {
    { { CharBoxPosition::TOP_LEFT, CharBoxPosition::TOP_RIGHT },
      { CharBoxPosition::TOP_RIGHT, CharBoxPosition::BOTTOM_RIGHT },
      { CharBoxPosition::BOTTOM_RIGHT, CharBoxPosition::BOTTOM_LEFT },
      { CharBoxPosition::BOTTOM_LEFT, CharBoxPosition::TOP_LEFT },
      { CharBoxPosition::LEFT_MIDDLE, CharBoxPosition::RIGHT_MIDDLE } } };

const std::array< std::pair< CharBoxPosition, CharBoxPosition >, 4 > NUMBER_NINE = {
    { { CharBoxPosition::TOP_LEFT, CharBoxPosition::TOP_RIGHT },
      { CharBoxPosition::TOP_RIGHT, CharBoxPosition::BOTTOM_RIGHT },
      { CharBoxPosition::TOP_LEFT, CharBoxPosition::LEFT_MIDDLE },
      { CharBoxPosition::LEFT_MIDDLE, CharBoxPosition::RIGHT_MIDDLE } } };
