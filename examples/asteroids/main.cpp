#include "AsteroidRenderers.hpp"
#include "AsteroidUpdates.hpp"
#include "AsteroidInit.hpp"
#include "AsteroidInputs.hpp"

#include "Game.hpp"

int main()
{
    game.initFunc = InitializeAsteroidGame;

    game.renderFuncs.push_back( RenderShip );
    game.renderFuncs.push_back( RenderAsteroids );
    game.renderFuncs.push_back( RenderBullets );

    game.updateFuncs.push_back( UpdateAsteroids );
    game.updateFuncs.push_back( UpdateBullets );

    game.inputHandlerFuncs.push_back( HandleInput );

    game.Start();
}