#include "modules/drawing/include/DrawUtils.hpp"
#include <vector>

constexpr size_t width = 100;
constexpr size_t height = 50;

std::vector< std::vector< char > > frameBuf =
    std::vector< std::vector< char > >( height, std::vector< char >( width ) );

int main()
{
    DrawUtils::Clear( frameBuf, '.' );

    // DrawUtils::DrawLineV2({0,0}, {width - 1, 0}, frameBuf, 'X');
    // DrawUtils::DrawLineV2({0,height - 1}, {width - 1, height-1}, frameBuf, 'X');
    // DrawUtils::DrawLineV2({0,0}, {0, height-1}, frameBuf, 'X');
    // DrawUtils::DrawLineV2({width-1,0}, {width-1, height-1}, frameBuf, 'X');
    // DrawUtils::DrawLineV2({0,0}, {width-1, height-1}, frameBuf, 'X');
    // DrawUtils::DrawLineV2({0,0}, {width-1, height-1}, frameBuf, 'X');
    // DrawUtils::DrawLineV2({0,height-1}, {width-1, 0}, frameBuf, 'X');

    DrawUtils::DrawLineV2({0,0}, {width / 2, height / 8}, frameBuf, 'X');
    // DrawUtils::DrawLineV3({0,0}, {width / 2, height / 8}, frameBuf, 'X');


    // DrawUtils::DrawLine({0,0}, {width - 1, 0}, frameBuf, 'X');
    // DrawUtils::DrawLine({0,height - 1}, {width - 1, height-1}, frameBuf, 'X');
    // DrawUtils::DrawLine({0,0}, {0, height-1}, frameBuf, 'X');
    // DrawUtils::DrawLine({width-1,0}, {width-1, height-1}, frameBuf, 'X');
    // DrawUtils::DrawLine({0,0}, {width-1, height-1}, frameBuf, 'X');
    // DrawUtils::DrawLine({0,0}, {width-1, height-1}, frameBuf, 'X');
    // DrawUtils::DrawLine({0,height-1}, {width-1, 0}, frameBuf, 'X');

    // DrawUtils::DrawTriangle(
    //     {0, height - 1},
    //     {width-1, height-1},
    //     {width/2, 0},
    //     frameBuf,
    //     'X'
    // );
    // DrawUtils::DrawTriangle(
    //     {0, 0},
    //     {width-1, 0},
    //     {width/2, height-1},
    //     frameBuf,
    //     'X'
    // );

    DrawUtils::Draw( frameBuf );
}