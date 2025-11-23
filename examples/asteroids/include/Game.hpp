#include "DrawUtils.hpp"
#include "Entity.hpp"
#include "Frame.hpp"
#include "KeyboardInputHandler.hpp"
#include <functional>

struct Game
{
    Frame screen = Frame{ 500, 200 };
    bool gameRunning = true;
    bool gamePaused = false;

    long frameTimeMs = 16; // Approx 60fps

    std::vector< Entity > entities;
    std::vector< std::function< void( std::vector< Entity >& ) > > updateFuncs;
    std::vector< std::function< void( std::vector< Entity >&, Frame& frame ) > > renderFuncs;

    void Start()
    {
        InputCommon::KeyboardInputHandler kbd;
        DrawUtils::SetToSystemLocale();
        kbd.Start();

        while ( gameRunning )
        {
            std::this_thread::sleep_for( std::chrono::milliseconds( frameTimeMs ) );

            if ( gamePaused )
                continue;

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
};