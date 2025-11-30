#pragma once
#include <array>
#include "Frame.hpp"
#include "Color.hpp"

struct GameWorld;
struct GameState;

void UpdateAsteroids( GameWorld& gameWorld, GameState& gameSettings, Frame& screen );
void UpdateBullets( GameWorld& gameWorld, GameState& gameSettings, Frame& screen );
void UpdateCollisions( GameWorld& gameWorld, GameState& gameSettings, Frame& screen );


inline std::array< void ( * )( GameWorld& gameWorld, GameState& gameSettings, Frame& screen ), 3 > 
updateTable = 
{
    UpdateAsteroids, 
    UpdateBullets,
        UpdateCollisions 
};

#ifdef AUTARKEIA_DEBUG_ENABLED

// void DebugCollisionColors( Sprite& sprite, bool collisionOccurred );
void DebugCollisionColors( Color& color, bool collisionOccurred );

#endif