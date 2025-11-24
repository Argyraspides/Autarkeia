#pragma once
#include "DrawUtils.hpp"
#include "Frame.hpp"
#include "KeyboardInputHandler.hpp"
#include <functional>
#include <list>

#include "Asteroid.hpp"
#include "Bullet.hpp"
#include "Characters.hpp"
#include "Ship.hpp"

struct GameWorld
{
    long asteroidGenerationPeriodMs = 5000;

    std::list< Bullet > bullets;
    std::list< Asteroid > asteroids;

    Ship ship;
};

struct GameSettings
{
    bool gameRunning = true;
    bool gamePaused = false;

    long frameTimeMs = 16; // Approx 60fps

    int shipRotSpeed = 10;
};

struct Game
{
  private:
    GameWorld gameWorld;
    GameSettings gameSettings;

    Frame screen = Frame{ 500, 200 };

    InputCommon::KeyboardInputHandler kbd;

  public:
    std::vector< std::function< void( GameWorld&, GameSettings&, InputCommon::KeyboardInputHandler& ) > >
        inputHandlerFuncs;
    std::vector< std::function< void( GameWorld&, Frame& ) > > renderFuncs;
    std::vector< std::function< void( GameWorld&, Frame& ) > > updateFuncs;

    void Start()
    {
        DrawUtils::SetToSystemLocale();
        kbd.Start();

        while ( gameSettings.gameRunning )
        {
            std::this_thread::sleep_for( std::chrono::milliseconds( gameSettings.frameTimeMs ) );

            if ( gameSettings.gamePaused )
                continue;

            for ( auto& inputHandlerFunc : inputHandlerFuncs )
                inputHandlerFunc( gameWorld, gameSettings, kbd );

            for ( auto& updateFunc : updateFuncs )
                updateFunc( gameWorld, screen );

            DrawUtils::ClearFrame( screen, SHADE_0 );
            DrawUtils::DrawBorderOnFrame( screen );

            for ( auto& renderFunc : renderFuncs )
                renderFunc( gameWorld, screen );

            DrawUtils::ResetTerminalCursor();
            DrawUtils::DrawFrame( screen );
        }
    }

    void Stop()
    {
        gameSettings.gameRunning = false;
    }
} inline game;