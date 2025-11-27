#pragma once
#include "DrawUtils.hpp"
#include "Frame.hpp"
#include "KeyboardInputHandler.hpp"
#include <list>

#include "Asteroid.hpp"
#include "Bullet.hpp"
#include "Characters.hpp"
#include "Ship.hpp"

#include "AsteroidInit.hpp"
#include "AsteroidRenderers.hpp"
#include "AsteroidUpdates.hpp"
#include "AsteroidInputs.hpp"

struct GameWorld
{
    std::list< Bullet > bullets;
    std::list< Asteroid > asteroids;

    Ship ship;

    int collisions = 0;
};

struct GameSettings
{
    bool gameRunning = true;
    bool gamePaused = false;

    long frameTimeMs = 16; // Approx 60fps

    int shipRotSpeed = 10;
    int shipHealth = 100;

    long asteroidGenerationPeriodMs = 5000;
    int asteroidDamage = 5;
};

struct Game
{
  private:
    GameWorld gameWorld;
    GameSettings gameSettings;

    Frame screen = Frame{ 500, 200 };

    InputCommon::KeyboardInputHandler kbd;

  public:
    void Start()
    {
        DrawUtils::SetToSystemLocale();
        kbd.Start();

        InitializeGame( gameWorld, screen );
        while ( gameSettings.gameRunning )
        {
            std::this_thread::sleep_for( std::chrono::milliseconds( gameSettings.frameTimeMs ) );

            if ( gameSettings.gamePaused )
                continue;

            for ( auto& inputHandlerFunc : inputTable )
                inputHandlerFunc( gameWorld, gameSettings, kbd );

            for ( auto& updateFunc : updateTable )
                updateFunc( gameWorld, gameSettings, screen );

            DrawUtils::ClearFrame( screen, SHADE_0 );
            DrawUtils::DrawBorder( screen );

            for ( auto& renderFunc : renderTable )
                renderFunc( gameWorld, screen );

            DrawUtils::ResetTerminalCursor();
            DrawUtils::RenderFrame( screen );
        }
    }

    void Stop()
    {
        gameSettings.gameRunning = false;
    }
} inline game;