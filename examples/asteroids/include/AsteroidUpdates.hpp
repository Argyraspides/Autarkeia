#pragma once
#include <array>
class Frame;
struct GameWorld;
struct GameSettings;

void UpdateAsteroids( GameWorld& gameWorld, GameSettings& gameSettings, Frame& screen );
void UpdateBullets( GameWorld& gameWorld, GameSettings& gameSettings, Frame& screen );

inline std::array< void ( * )( GameWorld& gameWorld, GameSettings& gameSettings, Frame& screen ), 2 > 
updateTable = 
{
    UpdateAsteroids, 
    UpdateBullets 
};