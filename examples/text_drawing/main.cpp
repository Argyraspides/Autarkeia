#include "Frame.hpp"
#include "Vec2I.hpp"

#include "DrawUtils.hpp"
#include "TextDrawUtils.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

int main()
{
    Frame f( 100, 25 );

    DrawUtils::Clear( f, '.' );
    DrawUtils::ClearScreen();

    for ( int i = 0; i < 1000; i++ )
    {
        int randomDim = std::clamp( rand() % 21, 5, 20) ;
        DrawUtils::DrawText( std::to_string( i ), { randomDim, randomDim}, f, 'x' );
        DrawUtils::Draw( f );
        std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );
        DrawUtils::Clear( f, '.' );
        DrawUtils::ClearScreen();
    }

    std::cin.get();
}