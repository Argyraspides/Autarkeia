//
// Created by gaugamela on 9/24/25.
//

#include "DrawUtils.hpp"
#include "Frame.hpp"
#include "KeyboardInputHandler.hpp"
#include "TextDrawUtils.hpp"
#include "Vec2I.hpp"
#include <chrono>
#include <iostream>
#include <linux/input-event-codes.h>
#include <thread>

Vec2I boardSize = { 50, 35 };
Vec2I nextSnakeFoodLocation = { 20, 20 };

struct SnakePoint
{
    SnakePoint()
    {
    }

    SnakePoint( Vec2I loc, Vec2I vel )
        : location( loc ),
          velocity( vel )
    {
    }
    Vec2I location;
    Vec2I velocity;
};

SnakePoint snakeHead;
SnakePoint snakeTail;
std::vector< SnakePoint > anchorPoints;

size_t frameTimeMs = 75;
Frame frame{ boardSize.x, boardSize.y };

FrameSection scoreSection = FrameSection::ONE;
FrameSection gameSection = FrameSection::TWO;

// Game score section
Vec2I scoreSectionOffset = { 0, 0 };
Vec2I scoreSectionDimension = { boardSize.x, 10 };

// Main game section
Vec2I gameSectionOffset = { 0, scoreSectionDimension.y };
Vec2I gameSectionDimension = { boardSize.x, boardSize.y - scoreSectionDimension.y };

InputCommon::KeyboardInputHandler kbd;

bool pauseGame = false;
bool gameRunning = true;
bool playerWon = false;
size_t snakeSize = 0;

void SetupSections()
{
    frame.SetSection( scoreSection, scoreSectionOffset, scoreSectionDimension );
    frame.SetSection( gameSection, gameSectionOffset, gameSectionDimension );
}

void GrowSnake()
{
    Vec2I newPoint = snakeTail.location - snakeTail.velocity;
    snakeTail.location = newPoint;
    anchorPoints[ 0 ] = snakeTail;
    nextSnakeFoodLocation = { rand() % gameSectionDimension.x, rand() % gameSectionDimension.y };
    snakeSize++;
}

void CheckSnakeIntersection()
{
    if ( snakeSize < 4 )
        return;

    for ( int i = 0; i < anchorPoints.size() - 2; i++ )
    {
        Vec2I p1 = anchorPoints[ i ].location;
        Vec2I p2 = anchorPoints[ i + 1 ].location;

        bool lineVertical = p1.x == p2.x;
        bool headOnLine = false;
        bool headInBounds = false;
        if ( lineVertical )
        {
            Vec2I topPt = p1.y < p2.y ? p1 : p2;
            Vec2I bottomPt = p1.y > p2.y ? p1 : p2;

            headOnLine = snakeHead.location.x == p1.x;
            headInBounds = snakeHead.location.y <= bottomPt.y && snakeHead.location.y >= topPt.y;
        }
        else
        {
            Vec2I leftPt = p1.x < p2.x ? p1 : p2;
            Vec2I rightPt = p1.x > p2.x ? p1 : p2;

            headOnLine = snakeHead.location.y == p1.y;
            headInBounds = snakeHead.location.x >= leftPt.x && snakeHead.location.x <= rightPt.x;
        }

        if ( headOnLine && headInBounds )
        {
            gameRunning = false;
            return;
        }
    }
}

void UpdateSnake()
{
    if ( snakeHead.location == nextSnakeFoodLocation )
        GrowSnake();

    // If we hit an anchor point, change velocity
    // First and last pt is always head/tail of snake
    if ( snakeHead.location == anchorPoints.at( anchorPoints.size() - 2 ).location )
        snakeHead.velocity = anchorPoints.at( anchorPoints.size() - 2 ).velocity;

    if ( snakeTail.location == anchorPoints.at( 1 ).location )
    {
        snakeTail.velocity = anchorPoints.at( 1 ).velocity;

        if ( anchorPoints.size() > 2 )
            anchorPoints.erase( anchorPoints.begin() + 1 );
    }

    snakeHead.location += snakeHead.velocity;
    snakeTail.location += snakeTail.velocity;

    // Collision with wall
    if ( snakeHead.location.x >= boardSize.x )
        gameRunning = false;
    else if ( snakeHead.location.x < 0 )
        gameRunning = false;

    if ( snakeHead.location.y >= boardSize.y )
        gameRunning = false;
    else if ( snakeHead.location.y < 0 )
        gameRunning = false;

    if ( snakeTail.location.x >= boardSize.x )
        gameRunning = false;
    else if ( snakeTail.location.x < 0 )
        gameRunning = false;

    if ( snakeTail.location.y >= boardSize.y )
        gameRunning = false;
    else if ( snakeTail.location.y < 0 )
        gameRunning = false;

    anchorPoints[ 0 ] = snakeTail;
    anchorPoints[ anchorPoints.size() - 1 ] = snakeHead;

    CheckSnakeIntersection();
}

void UpdateSpeed()
{
    static int originalFrameTime = frameTimeMs;
    frameTimeMs = originalFrameTime - snakeSize; 
}

void HandleUserInput()
{
    std::optional< InputCommon::KeyInputCode > keyPress = kbd.GetNextKeyPress();

    if ( !keyPress )
        return;

    switch ( keyPress.value() )
    {
    case KEY_W:
    case KEY_UP: {
        if ( snakeHead.velocity == VEC2I_DOWN || snakeHead.velocity == VEC2I_UP )
            return;
        anchorPoints.insert( anchorPoints.end() - 1, { snakeHead.location, VEC2I_UP } );
        break;
    }
    case KEY_A:
    case KEY_LEFT: {
        if ( snakeHead.velocity == VEC2I_RIGHT || snakeHead.velocity == VEC2I_LEFT )
            return;
        anchorPoints.insert( anchorPoints.end() - 1, { snakeHead.location, VEC2I_LEFT } );
        break;
    }
    case KEY_S:
    case KEY_DOWN: {
        if ( snakeHead.velocity == VEC2I_UP || snakeHead.velocity == VEC2I_DOWN )
            return;
        anchorPoints.insert( anchorPoints.end() - 1, { snakeHead.location, VEC2I_DOWN } );
        break;
    }
    case KEY_D:
    case KEY_RIGHT: {
        if ( snakeHead.velocity == VEC2I_LEFT || snakeHead.velocity == VEC2I_RIGHT )
            return;
        anchorPoints.insert( anchorPoints.end() - 1, { snakeHead.location, VEC2I_RIGHT } );
        break;
    }
    case KEY_GRAVE: {
        GrowSnake();
        break;
    }
    case KEY_P: {
        pauseGame = !pauseGame;
        break;
    }
    }
}

void RenderScore()
{
    DrawUtils::Clear( frame, '.', scoreSection );
    DrawUtils::DrawText( std::to_string( snakeSize ), Vec2I{ 10, scoreSectionDimension.y - 2 }, frame, '@' );
    DrawUtils::DrawLine( { 0, scoreSectionDimension.y - 1 },
                         { scoreSectionDimension.x - 1, scoreSectionDimension.y - 1 }, frame, '_' );
}

void RenderSnake()
{
    DrawUtils::Clear( frame, '.', gameSection );
    static const char snakeChar = 'x';
    for ( int i = 0; i < anchorPoints.size() - 1; i++ )
    {
        Vec2I p1 = anchorPoints[ i ].location;
        Vec2I p2 = anchorPoints[ i + 1 ].location;
        DrawUtils::QuickDrawLine( p1, p2, frame, snakeChar, gameSection );
    }

    static const char foodChar = '0';
    DrawUtils::DrawPixel( nextSnakeFoodLocation, frame, foodChar, gameSection );
}

void Render()
{
    DrawUtils::ResetTerminalCursor();
    RenderScore();
    RenderSnake();
    DrawUtils::Draw( frame );
}
int main()
{
    snakeHead.location = ( boardSize / 2 );
    snakeTail.location = snakeHead.location;

    snakeHead.velocity = VEC2I_RIGHT;
    snakeTail.velocity = VEC2I_RIGHT;

    anchorPoints.push_back( snakeTail );
    anchorPoints.push_back( snakeHead );

    SetupSections();

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
        Render();
        if ( pauseGame )
            continue;

        UpdateSnake();
        UpdateSpeed();

        if ( snakeSize == boardSize.x * boardSize.y )
        {
            playerWon = true;
            gameRunning = false;
        }
    }

    if ( playerWon )
        std::cout << "YOU WON LETS FUCKING GO THAT'S BASICALLY IMPOSSIBLE" << std::endl;
    else
        std::cout << "YOU LOST!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;

    kbd.Stop();
}