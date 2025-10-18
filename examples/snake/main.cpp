//
// Created by gaugamela on 9/24/25.
//

#include "Vec2I.hpp"
#include "DrawUtils.hpp"
#include "Frame.hpp"
#include "KeyboardInputHandler.hpp"

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
    InputCommon::KeyboardInputHandler kbd;
    kbd.Start();

    auto startTime = std::chrono::steady_clock::now();
    while ( true )
    {
        auto now = std::chrono::steady_clock::now();
        auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime);

        const char snakeChar = 'x';
        DrawUtils::Clear( frame, '.' );
        DrawUtils::ClearScreen();

        for (const Vec2I& snakePt : snakePoints )
            DrawUtils::DrawPixel( snakePt, frame, snakeChar );

        DrawUtils::Draw( frame );
    }
}
