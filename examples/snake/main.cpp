//
// Created by gaugamela on 9/24/25.
//

#include "DrawUtils.hpp"
#include "Frame.hpp"
#include "KeyboardInputHandler.hpp"
#include "Vec2I.hpp"
#include <cassert>
#include <chrono>
#include <linux/input-event-codes.h>
#include <thread>
#include <unordered_map>
#include <vector>
#include <iostream>

Vec2I boardSize = { 25, 25 };

std::unordered_set< Vec2I, Vec2IHash > anchorPoints;

// First element is always the tail coz it completes the lines you have to check for
// snake intersection with itself
std::vector< Vec2I > anchorPointsList;

std::unordered_map< Vec2I, Vec2I, Vec2IHash, Vec2IEquality > anchorVelocities;
std::unordered_map< Vec2I, int, Vec2IHash, Vec2IEquality > anchorPointHits;

std::vector< Vec2I > snakeVelocities;
std::vector< Vec2I > snakePoints;

Vec2I snakeFood = { 20, 20 };

size_t frameTimeMs = 75;
Frame frame{ boardSize.x, boardSize.y };

InputCommon::KeyboardInputHandler kbd;

bool pauseGame = false;
bool gameRunning = true;
bool playerWon = false;

void GrowSnake()
{
    snakeFood = { rand() % frame.Width(), rand() % frame.Height() };
    snakePoints.push_back( snakePoints.back() - snakeVelocities.back() );
    snakeVelocities.push_back( snakeVelocities.back() );
}

void UpdateSnake()
{
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
                anchorPointsList.erase( anchorPointsList.begin() + 1 );
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

    if ( snakePoints.front() == snakeFood )
        GrowSnake();

    anchorPointsList[ 0 ] = snakePoints.back();

    if ( anchorPointsList.size() >= 2 )
    {
        Vec2I snakeHead = snakePoints.front();

        for ( int i = 0; i < anchorPointsList.size() - 1; i++ )
        {
            const Vec2I& p1 = anchorPointsList[ i ];
            const Vec2I& p2 = anchorPointsList[ i + 1 ];

            bool lineVertical = p1.x == p2.x;
            bool headOnLine = false;
            bool headInBounds = false;
            if ( lineVertical )
            {
                Vec2I topPt = p1.y < p2.y ? p1 : p2;
                Vec2I bottomPt = p1.y > p2.y ? p1 : p2;

                headOnLine = snakeHead.x == p1.x;
                headInBounds = snakeHead.y <= bottomPt.y && snakeHead.y >= topPt.y;
            }
            else
            {
                Vec2I leftPt = p1.x < p2.x ? p1 : p2;
                Vec2I rightPt = p1.x > p2.x ? p1 : p2;

                headOnLine = snakeHead.y == p1.y;
                headInBounds = snakeHead.x >= leftPt.x && snakeHead.x <= rightPt.x;
            }

            if ( headOnLine && headInBounds )
            {
                gameRunning = false;
                playerWon = false;
            }
        }
    }
}

void HandleUserInput()
{
    std::optional< InputCommon::KeyInputCode > keyPress = kbd.GetNextKeyPress();

    if ( !keyPress )
        return;

    Vec2I& headVel = snakeVelocities.front();

    switch ( keyPress.value() )
    {
    case KEY_W:
    case KEY_UP: {
        if ( headVel == VEC2I_DOWN || headVel == VEC2I_UP )
            return;
        anchorPoints.insert( snakePoints.front() );
        anchorPointsList.push_back( snakePoints.front() );
        anchorVelocities[ snakePoints.front() ] = VEC2I_UP;
        break;
    }
    case KEY_A:
    case KEY_LEFT: {
        if ( headVel == VEC2I_RIGHT || headVel == VEC2I_LEFT )
            return;
        anchorPoints.insert( snakePoints.front() );
        anchorPointsList.push_back( snakePoints.front() );
        anchorVelocities[ snakePoints.front() ] = VEC2I_LEFT;
        break;
    }
    case KEY_S:
    case KEY_DOWN: {
        if ( headVel == VEC2I_UP || headVel == VEC2I_DOWN )
            return;
        anchorPoints.insert( snakePoints.front() );
        anchorPointsList.push_back( snakePoints.front() );
        anchorVelocities[ snakePoints.front() ] = VEC2I_DOWN;
        break;
    }
    case KEY_D:
    case KEY_RIGHT: {
        if ( headVel == VEC2I_LEFT || headVel == VEC2I_RIGHT )
            return;
        anchorPoints.insert( snakePoints.front() );
        anchorPointsList.push_back( snakePoints.front() );
        anchorVelocities[ snakePoints.front() ] = VEC2I_RIGHT;
        break;
    }
    case KEY_SPACE: {
        GrowSnake();
        break;
    }
    case KEY_P: {
        pauseGame = !pauseGame;
        break;
    }
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

    for ( const Vec2I& anchorPoint : anchorPointsList )
        DrawUtils::DrawPixel( anchorPoint, frame, 'A' );

    DrawUtils::Draw( frame );
}

int main()
{
    snakePoints.push_back( boardSize / 2 );
    snakeVelocities.push_back( { -1, 0 } );
    anchorPointsList.push_back( snakePoints.front() );
    kbd.Start();

    auto startTime = std::chrono::steady_clock::now();
    while ( gameRunning )
    {
        auto nextFrameTime = startTime + std::chrono::milliseconds( frameTimeMs - 1 );
        auto now = std::chrono::steady_clock::now();
        auto timeToWait = nextFrameTime - now;

        std::this_thread::sleep_for( timeToWait );

        auto trueNextFrameTime = std::chrono::steady_clock::now() + std::chrono::milliseconds( 1 );
        while ( std::chrono::steady_clock::now() < trueNextFrameTime )
            ;

        startTime = std::chrono::steady_clock::now();

        HandleUserInput();

        if ( pauseGame )
        {
            continue;
        }

        UpdateSnake();
        Render();

        if ( snakePoints.size() == boardSize.x * boardSize.y )
        {
            playerWon = true;
            gameRunning = false;
        }
    }

    if(playerWon)
    {
        std::cout << "YOU WON LETS FUCKING GO THAT'S BASICALLY IMPOSSIBLE" << std::endl;
    }
    else 
    {
        std::cout << "YOU LOST!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    }

    kbd.Stop();
}