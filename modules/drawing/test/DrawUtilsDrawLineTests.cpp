//
// Created by gaugamela on 8/31/25.
//

#include "catch_amalgamated.hpp"
#include "DrawUtils.hpp"
#include "DrawUtilsConvenienceFunctions.hpp"

TEST_CASE("DrawUtils::DrawLine - Top horizontal line")
{
    const Vec2I gridSize = { 100, 100 };
    INITIALIZE_FRAMEBUF(gridSize);
    const char drawChar = 'c';
    DrawUtils::DrawLine({0,0}, {gridSize.x - 1, 0}, grid, drawChar);

    for (int x = 0; x < gridSize.x; x++)
    {
        CHECK(grid[0][x] == drawChar);
    }

    // Check nothing else is drawn to
    for (int y = 1; y < gridSize.y; y++)
    {
        for (int x = 0; x < gridSize.x; x++)
        {
            CHECK(grid[y][x] == DEFAULT_FRAMEBUF_CHAR);
        }
    }

}

TEST_CASE("DrawUtils::DrawLine - Diag line from top left to bottom right")
{
    const Vec2I gridSize = { 100, 100 };
    INITIALIZE_FRAMEBUF(gridSize);
    const char drawChar = 'c';
    DrawUtils::DrawLine({0,0}, {gridSize.x - 1, gridSize.y - 1}, grid, drawChar);


    for (int x = 0, y = 0; x < gridSize.x && y < gridSize.y; x++, y++)
    {
        CHECK(grid[y][x] == drawChar);
    }

    // Check nothing else is drawn to
    for (int y = 0; y < gridSize.y; y++)
    {
        for (int x = 0; x < gridSize.x; x++)
        {
            if (x == y)
            {
                continue;
            }
            CHECK(grid[y][x] == DEFAULT_FRAMEBUF_CHAR);
        }
    }

}

TEST_CASE("DrawUtils::DrawLine - Diag line from bottom right to top left")
{
    const Vec2I gridSize = { 100, 100 };
    INITIALIZE_FRAMEBUF(gridSize);
    const char drawChar = 'c';
    DrawUtils::DrawLine({gridSize.x - 1, gridSize.y - 1}, {0,0}, grid, drawChar);


    for (int x = 0, y = 0; x < gridSize.x && y < gridSize.y; x++, y++)
    {
        CHECK(grid[y][x] == drawChar);
    }

    // Check nothing else is drawn to
    for (int y = 0; y < gridSize.y; y++)
    {
        for (int x = 0; x < gridSize.x; x++)
        {
            if (x == y)
            {
                continue;
            }
            CHECK(grid[y][x] == DEFAULT_FRAMEBUF_CHAR);
        }
    }

}

TEST_CASE("DrawUtils::DrawLine - Vertical line from top left corner")
{
    const Vec2I gridSize = { 100, 100 };
    INITIALIZE_FRAMEBUF(gridSize);
    const char drawChar = 'c';
    DrawUtils::DrawLine({0, 0}, {0, gridSize.y - 1}, grid, drawChar);


    for (int y = 0; y < gridSize.y; y++)
    {
        CHECK(grid[y][0] == drawChar);
    }

    // Check nothing else is drawn to
    for (int y = 0; y < gridSize.y; y++)
    {
        for (int x = 1; x < gridSize.x; x++)
        {
            CHECK(grid[y][x] == DEFAULT_FRAMEBUF_CHAR);
        }
    }
}