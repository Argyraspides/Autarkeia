//
// Created by gaugamela on 8/24/25.
//

#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "DrawUtils.hpp"

TEST_CASE("DrawUtils::Clear fills grid with specified character", "[DrawUtils]") {
    std::vector<std::vector<char>> grid(10, std::vector<char>(10, 'a'));

    DrawUtils::Clear(grid, '.');

    for (const auto& row : grid) {
        for (char cell : row) {
            REQUIRE(cell == '.');
        }
    }
}