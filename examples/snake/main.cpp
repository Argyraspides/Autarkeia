//
// Created by gaugamela on 9/24/25.
//

#include "DrawUtils.hpp"
#include "Frame.hpp"
#include "KeyboardInputHandler.hpp"
#include "Vec2I.hpp"
#include <chrono>
#include <linux/input-event-codes.h>
#include <unordered_map>
#include <vector>

Vec2I boardSize = { 25, 25 };

std::unordered_set< Vec2I, Vec2IHash > anchorPoints;
std::unordered_set< Vec2I, Vec2IHash > anchorVelocities;

std::unordered_map< Vec2I, int, Vec2IHash, Vec2IEquality > anchorPointHits;

std::vector< Vec2I > snakeVelocities;
std::vector< Vec2I > snakePoints;

size_t frameTimeMs = 100;

void UpdateSnakePositions()
{
    // Update velocities based on the anchor points hit
    for ( int i = 0; i < snakePoints.size(); i++ )
    {
        Vec2I& pt = snakePoints[ i ];

        if ( !anchorPoints.contains( pt ) )
        {
            continue;
        }

        snakeVelocities[ i ] = *anchorPoints.find( pt );
        if ( ++anchorPointHits[ pt ] == snakePoints.size() )
        {
            anchorPointHits.erase( pt );
        }
    }

    for ( int i = 0; i < snakePoints.size(); i++ )
    {
        Vec2I& pt = snakePoints[ i ];
        pt += snakeVelocities[ i ];
    }
}

int main()
{

    snakePoints.push_back( boardSize / 2 );
    snakeVelocities.push_back( { -1, 0 } );

    Frame frame{ boardSize.x, boardSize.y };
    InputCommon::KeyboardInputHandler kbd;
    kbd.Start();

    auto startTime = std::chrono::steady_clock::now();
    while ( true )
    {
        auto now = std::chrono::steady_clock::now();
        auto deltaTime = std::chrono::duration_cast< std::chrono::milliseconds >( now - startTime );

        if ( deltaTime < std::chrono::milliseconds( frameTimeMs ) )
        {
            continue;
        }

        startTime += std::chrono::milliseconds( frameTimeMs );

        static const char snakeChar = 'x';
        DrawUtils::Clear( frame, '.' );
        DrawUtils::ClearScreen();

        UpdateSnakePositions();

        for ( const Vec2I& snakePt : snakePoints )
            DrawUtils::DrawPixel( snakePt, frame, snakeChar );

        DrawUtils::Draw( frame );

        std::optional< InputCommon::KeyInputCode > keyPress = kbd.GetNextKeyPress();

        if ( !keyPress )
        {
            continue;
        }

        switch ( keyPress.value() )
        {
        case KEY_W:
            anchorPoints.insert( snakePoints.front() );
            anchorVelocities.insert( VEC2I_UP );
            break;
        case KEY_A:
            anchorPoints.insert( snakePoints.front() );
            anchorVelocities.insert( VEC2I_LEFT );
            break;
        case KEY_S:
            anchorPoints.insert( snakePoints.front() );
            anchorVelocities.insert( VEC2I_DOWN );
            break;
        case KEY_D:
            anchorPoints.insert( snakePoints.front() );
            anchorVelocities.insert( VEC2I_RIGHT );
            break;
        }
    }
}
