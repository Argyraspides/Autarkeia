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
std::unordered_map< Vec2I, Vec2I, Vec2IHash, Vec2IEquality > anchorVelocities;
std::unordered_map< Vec2I, int, Vec2IHash, Vec2IEquality > anchorPointHits;

Vec2I snakeFood = { 20, 20 };

std::vector< Vec2I > snakeVelocities;
std::vector< Vec2I > snakePoints;

size_t frameTimeMs = 100;
Frame frame{ boardSize.x, boardSize.y };

InputCommon::KeyboardInputHandler kbd;

void UpdateSnake()
{
    if ( snakePoints.front() == snakeFood )
    {
        snakeFood = { rand() % frame.Width(), rand() % frame.Height() };
        snakePoints.push_back( snakePoints.back() - snakeVelocities.back() );
        snakeVelocities.push_back( snakeVelocities.back() );
    }

    // Update velocities based on the anchor points hit
    for ( int i = 0; i < snakePoints.size(); i++ )
    {
        Vec2I& pt = snakePoints[ i ];

        if ( anchorPoints.contains( pt ) )
        {
            snakeVelocities[ i ] = anchorVelocities[ pt ];
            if ( ++anchorPointHits[ pt ] == snakePoints.size() )
            {
                anchorPoints.erase( pt );
                anchorVelocities.erase( pt );
                anchorPointHits.erase( pt );
            }
        }

        pt += snakeVelocities[ i ];

        if ( pt.x >= frame.Width() )
            pt.x = 0;

        if ( pt.x < 0 )
            pt.x = frame.Width() - 1;

        if ( pt.y >= frame.Height() )
            pt.y = 0;

        if ( pt.y < 0 )
            pt.y = frame.Height() - 1;
    }
}

void HandleUserInput()
{
    std::optional< InputCommon::KeyInputCode > keyPress = kbd.GetNextKeyPress();

    if ( !keyPress )
        return;

    switch ( keyPress.value() )
    {
    case KEY_W:
        anchorPoints.insert( snakePoints.front() );
        anchorVelocities[ snakePoints.front() ] = VEC2I_UP;
        break;
    case KEY_A:
        anchorPoints.insert( snakePoints.front() );
        anchorVelocities[ snakePoints.front() ] = VEC2I_LEFT;
        break;
    case KEY_S:
        anchorPoints.insert( snakePoints.front() );
        anchorVelocities[ snakePoints.front() ] = VEC2I_DOWN;
        break;
    case KEY_D:
        anchorPoints.insert( snakePoints.front() );
        anchorVelocities[ snakePoints.front() ] = VEC2I_RIGHT;
        break;
    }
}

void Render()
{
    static const char snakeChar = 'x';
    DrawUtils::Clear( frame, '.' );
    DrawUtils::ClearScreen();

    for ( const Vec2I& snakePt : snakePoints )
        DrawUtils::DrawPixel( snakePt, frame, snakeChar );

    static const char foodChar = '0';
    DrawUtils::DrawPixel( snakeFood, frame, foodChar );

    DrawUtils::Draw( frame );
}

int main()
{
    snakePoints.push_back( boardSize / 2 );
    snakeVelocities.push_back( { -1, 0 } );
    kbd.Start();

    auto startTime = std::chrono::steady_clock::now();
    while ( true )
    {
        auto now = std::chrono::steady_clock::now();
        auto deltaTime = std::chrono::duration_cast< std::chrono::milliseconds >( now - startTime );

        if ( deltaTime < std::chrono::milliseconds( frameTimeMs ) )
            continue;

        startTime += std::chrono::milliseconds( frameTimeMs );

        HandleUserInput();
        UpdateSnake();
        Render();
    }
}
