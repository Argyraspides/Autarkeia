#include "Frame.hpp"
#include "Vec2I.hpp"

#include "DrawUtils.hpp"
#include "TextDrawUtils.hpp"

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

int main()
{
    Frame f( 100, 25 );

    DrawUtils::Clear( f, ' ' );
    DrawUtils::ClearScreen();

    for ( int i = 0; i < 100; i++ )
    {
        DrawUtils::DrawText( std::to_string( i ), { 10, 10 }, f, 'x' );
        DrawUtils::Draw( f );
        std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
        DrawUtils::Clear( f, ' ' );
        DrawUtils::ClearScreen();
    }

    std::cin.get();
}