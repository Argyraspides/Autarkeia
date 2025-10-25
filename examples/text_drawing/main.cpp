#include "Frame.hpp"
#include "Vec2I.hpp"

#include "DrawUtils.hpp"
#include "TextDrawUtils.hpp"

#include <iostream>

int main()
{
    Frame f(25, 25);

    DrawUtils::Clear(f, '-');
    DrawUtils::ClearScreen();
    DrawUtils::DrawText( "1", {10, 10}, f, 'x' );
    DrawUtils::Draw(f);

    std::cin.get();
}