#pragma once
#include "DrawUtils.hpp"
#include "Frame.hpp"
#include "PeripheralInputHandler.hpp"
#include <list>

#include "Asteroid.hpp"
#include "Bullet.hpp"
#include "Characters.hpp"
#include "Ship.hpp"

#include "AsteroidInit.hpp"
#include "AsteroidInputs.hpp"
#include "AsteroidRenderers.hpp"
#include "AsteroidUpdates.hpp"

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
    bool tickForward = true;

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

    InputCommon::PeripheralInputHandler kbd;

  public:
    void Start()
    {
        DrawUtils::SetToSystemLocale();
        DrawUtils::DisableEcho();
        DrawUtils::HideCursor();
        kbd.Start();

        InitializeGame( gameWorld, screen );
        while ( gameSettings.gameRunning )
        {
            std::this_thread::sleep_for( std::chrono::milliseconds( gameSettings.frameTimeMs ) );

            for ( auto& inputHandlerFunc : inputTable )
                inputHandlerFunc( gameWorld, gameSettings, kbd );

            if ( gameSettings.gamePaused )
            {
                if( gameSettings.tickForward )
                {
                    gameSettings.tickForward = false;
                }
                else
                {
                    continue;
                } 
            }

            for ( auto& updateFunc : updateTable )
                updateFunc( gameWorld, gameSettings, screen );

            DrawUtils::ClearFrame( screen, SHADE_0 );
            DrawUtils::DrawBorder( screen );

            for ( auto& renderFunc : renderTable )
                renderFunc( gameWorld, screen );

            DrawUtils::ResetTerminalCursor();
            DrawUtils::RenderFrame( screen );
        }

        DrawUtils::EnableEcho();
        DrawUtils::ShowCursor();
    }

    void Stop()
    {
        gameSettings.gameRunning = false;
    }
} inline game;