//
// Created by gaugamela on 8/24/25.
//

#include "catch_amalgamated.hpp"
#include "DrawUtils.hpp"
#include "DrawUtilsConvenienceFunctions.hpp"

TEST_CASE("DrawUtils::DrawPixel draws a pixel in the center")
{
    const int gridSize = 11;
    char drawChar = 'p';
    int center = gridSize / 2;

    DRAW_PIXEL(drawChar, gridSize, gridSize, center, center)

    DrawUtils::DrawPixel(p, grid, drawChar);

    CHECK(grid[center][center] == drawChar);
}

TEST_CASE("DrawUtils::DrawPixel draws a pixel in the top left corner")
{
    const int gridSize = 10;
    char drawChar = 'p';

    DRAW_PIXEL(drawChar, gridSize, gridSize, 0, 0)

    CHECK(grid[0][0] == drawChar);
}

TEST_CASE("DrawUtils::DrawPixel draws a pixel in the top right corner")
{
    const int gridSize = 10;
    char drawChar = 'p';

    DRAW_PIXEL(drawChar, gridSize, gridSize, gridSize - 1, gridSize - 1)

    CHECK(grid[gridSize - 1][gridSize - 1] == drawChar);
}

TEST_CASE("DrawUtils::DrawPixel draws a pixel in the bottom left corner")
{
    const int gridSize = 10;
    char drawChar = 'p';

    DRAW_PIXEL(drawChar, gridSize, gridSize, 0, gridSize - 1)

    CHECK(grid[gridSize - 1][0] == drawChar);
}

TEST_CASE("DrawUtils::DrawPixel draws a pixel in the bottom right corner")
{
    const int gridSize = 10;
    char drawChar = 'p';

    DRAW_PIXEL(drawChar, gridSize, gridSize, gridSize - 1, gridSize - 1)

    CHECK(grid[gridSize - 1][gridSize - 1] == drawChar);
}

TEST_CASE("DrawUtils::DrawPixel pixel out of bounds pos x and pos y")
{
    const int gridSize = 10;
    char drawChar = 'p';
    DRAW_PIXEL(drawChar, gridSize, gridSize, gridSize, gridSize)

    CHECK_CLEAR(DEFAULT_FRAMEBUF_CHAR) // If pixel is out of bounds, nothing should change
}

TEST_CASE("DrawUtils::DrawPixel pixel far out of bounds pos x and pos y")
{
    const int gridSize = 10;
    char drawChar = 'p';
    DRAW_PIXEL(drawChar, gridSize, gridSize, gridSize + 100, gridSize + 100)

    CHECK_CLEAR(DEFAULT_FRAMEBUF_CHAR) // If pixel is out of bounds, nothing should change
}

TEST_CASE("DrawUtils::DrawPixel pixel barely out of bounds neg x and neg y")
{
    const int gridSize = 10;
    char drawChar = 'p';
    DRAW_PIXEL(drawChar, gridSize, gridSize, -1, -1)

    CHECK_CLEAR(DEFAULT_FRAMEBUF_CHAR) // If pixel is out of bounds, nothing should change
}

TEST_CASE("DrawUtils::DrawPixel pixel far out of bounds neg x and neg y")
{
    const int gridSize = 10;
    char drawChar = 'p';
    DRAW_PIXEL(drawChar, gridSize, gridSize, -100, -100)

    CHECK_CLEAR(DEFAULT_FRAMEBUF_CHAR) // If pixel is out of bounds, nothing should change
}

TEST_CASE("DrawUtils::DrawPixel pixel out of bounds x OK pos y exceeded")
{
    const int gridSize = 10;
    char drawChar = 'p';
    DRAW_PIXEL(drawChar, gridSize, gridSize, 0, gridSize)

    CHECK_CLEAR(DEFAULT_FRAMEBUF_CHAR) // If pixel is out of bounds, nothing should change
}

TEST_CASE("DrawUtils::DrawPixel pixel out of bounds pos x exceeded y OK")
{
    const int gridSize = 10;
    char drawChar = 'p';
    DRAW_PIXEL(drawChar, gridSize, gridSize, gridSize, 0)

    CHECK_CLEAR(DEFAULT_FRAMEBUF_CHAR) // If pixel is out of bounds, nothing should change
}