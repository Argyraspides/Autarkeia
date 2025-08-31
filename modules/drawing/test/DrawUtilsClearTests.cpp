//
// Created by gaugamela on 8/31/25.
//

#include "catch_amalgamated.hpp"
#include "DrawUtils.hpp"
#include "DrawUtilsConvenienceFunctions.hpp"

TEST_CASE("DrawUtils::Clear fills grid with every character -- n x n", "[DrawUtils]") {

    std::vector<std::vector<char>> grid(10, std::vector<char>(10, '.'));

    for (char c = 0; c < std::numeric_limits< char >::max(); c++)
    {
        DrawUtils::Clear(grid, c);
        CHECK_CLEAR(c);
    }
}

TEST_CASE("DrawUtils::Clear fills grid with every character -- n x m, n > m", "[DrawUtils]") {

    std::vector<std::vector<char>> grid(10, std::vector<char>(5, '.'));

    for (char c = 0; c < std::numeric_limits< char >::max(); c++)
    {
        DrawUtils::Clear(grid, c);
        CHECK_CLEAR(c);
    }
}

TEST_CASE("DrawUtils::Clear fills grid with every character -- n x m, m > n", "[DrawUtils]") {

    std::vector<std::vector<char>> grid(5, std::vector<char>(10, '.'));

    for (char c = 0; c < std::numeric_limits< char >::max(); c++)
    {
        DrawUtils::Clear(grid, c);
        CHECK_CLEAR(c);
    }
}