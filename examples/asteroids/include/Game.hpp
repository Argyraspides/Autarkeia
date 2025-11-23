#pragma once
#include "DrawUtils.hpp"
#include "Entity.hpp"
#include "Frame.hpp"
#include "KeyboardInputHandler.hpp"
#include <functional>

#include "Asteroid.hpp"
#include "Bullet.hpp"
#include "Ship.hpp"
#include <list>

struct GameWorld
{
    long asteroidGenerationPeriodMs = 5000;

    std::list< Bullet > bullets;
    std::list< Asteroid > asteroids;

    Ship ship;
} inline gameWorld;

struct Game
{
    Frame screen = Frame{ 500, 200 };
    bool gameRunning = true;
    bool gamePaused = false;

    long frameTimeMs = 16; // Approx 60fps

    std::vector< Entity > entities;

    std::vector< std::function< void( std::vector< Entity >& ) > > updateFuncs;
    std::vector< std::function< void( InputCommon::KeyboardInputHandler& ) > > inputHandlerFuncs;
    std::vector< std::function< void( std::vector< Entity >&, Frame& frame ) > > renderFuncs;

    InputCommon::KeyboardInputHandler kbd;

    void Start()
    {
        DrawUtils::SetToSystemLocale();
        kbd.Start();

        while ( gameRunning )
        {
            std::this_thread::sleep_for( std::chrono::milliseconds( frameTimeMs ) );

            if ( gamePaused )
                continue;

            for ( auto& inputHandlerFunc : inputHandlerFuncs )
                inputHandlerFunc( kbd );

            for ( auto& updateFunc : updateFuncs )
                updateFunc( entities );

            for ( auto& renderFunc : renderFuncs )
                renderFunc( entities, screen );
        }
    }

    void Stop()
    {
        gameRunning = false;
    }
} inline game;