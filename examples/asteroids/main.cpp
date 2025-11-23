#include "Asteroid.hpp"
#include "Bullet.hpp"

#include "Characters.hpp"
#include "DrawUtils.hpp"
#include "Frame.hpp"
#include "KeyboardInputHandler.hpp"
#include "Vec2I.hpp"

#include <chrono>
#include <cmath>
#include <linux/input-event-codes.h>
#include <optional>
#include "Game.hpp"

Frame screen( 500, 200 );
long frameTimeMs = 16;

int rotationSpeed = 5;

bool paused = false;


void RenderLoop()
{
    DrawUtils::ClearFrame( screen, SHADE_0 );
    DrawUtils::DrawBorderOnFrame( screen );

    RenderBullets();
    RenderAsteroids();
    RenderShip();

    DrawUtils::ResetTerminalCursor();
    DrawUtils::DrawFrame( screen );
}
int main()
{
    game.Start();
}