#include "Frame.hpp"
#include "Vec2I.hpp"

#include "DrawUtils.hpp"
#include "TextDrawUtils.hpp"

#include <iostream>

int main()
{
    Frame f(100 , 25);

    DrawUtils::Clear(f, ' ');
    DrawUtils::ClearScreen();
    DrawUtils::DrawText( "ABCDEFG", { 5, 5 }, f, 'x' );
    DrawUtils::Draw(f);

    std::cin.get();
}