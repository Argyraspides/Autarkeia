#include "DrawUtils.hpp"
#include <array>
#include <cmath>
#include <iostream>
#include <vector>

constexpr size_t width = 100;
constexpr size_t height = 50;

std::vector< std::vector< char > > frameBuf =
    std::vector< std::vector< char > >( height, std::vector< char >( width ) );

int main()
{
    DrawUtils::Clear( frameBuf, '.' );
    DrawUtils::DrawLine( { 0, height - 1 }, { width - 1, height - 1 }, frameBuf, 'X' );
    DrawUtils::DrawLine( { 0, height - 1 }, { width / 2, 0 }, frameBuf, 'X' );
    DrawUtils::DrawLine( { width - 1, height - 1 }, { width / 2, 0 }, frameBuf, 'X' );
    DrawUtils::Draw( frameBuf );
}