//
// Created by gaugamela on 9/24/25.
//

#include <iostream>
#include <vector>
#include "Vec2I.hpp"
#include <thread>
#include "DrawUtils.hpp"

Vec2I boardSize = { 25, 25 };


int main()
{
    std::vector<Vec2I> anchorVelocities;
    std::vector<Vec2I> anchorPoints;

    std::vector<Vec2I> snakeVelocities;
    std::vector<Vec2I> snakePoints;

    snakePoints.push_back( boardSize / 2 );
    snakeVelocities.push_back( { -1, 0 } );

    Frame frame { boardSize.x, boardSize.y };

    while ( true )
    {
        std::this_thread::sleep_for( std::chrono::milliseconds(20) );
        DrawUtils::Clear( frame, '.' );
        DrawUtils::ClearScreen();
        DrawUtils::Draw( frame );
    }


}