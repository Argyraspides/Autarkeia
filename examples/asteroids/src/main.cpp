#include "DrawUtils.hpp"
#include "Frame.hpp"
#include "ShipSprite.hpp"
#include <chrono>

Frame screen( 35, 35 );

int main()
{
    DrawUtils::Clear( screen, ' ' );

    Sprite sprite( 20, 20 );
    DrawUtils::Clear( sprite.frame, DrawUtils::TRANSPARENT_CHAR );

    Vec2I p1, p2, p3;

    p1 = { sprite.frame.Width() / 2, 0 };
    p2 = { 1, sprite.frame.Height() - 1 };
    p3 = { sprite.frame.Width() - 2, sprite.frame.Height() - 1 };

    DrawUtils::QuickDrawTriangle( p1, p2, p3, sprite.frame, '.' );

    // No rotation (north)
    DrawUtils::DrawSprite( sprite, screen, { 10, 10 } );
    DrawUtils::Draw( screen );
    DrawUtils::Clear( screen, ' ' );

    // Rotation 1 (east)
    DrawUtils::RotateSprite( sprite );
    DrawUtils::DrawSprite( sprite, screen, { 10, 10 } );

    DrawUtils::Draw( screen );
    DrawUtils::Clear( screen, ' ' );

    // Rotation 2 (south)
    DrawUtils::RotateSprite( sprite );
    DrawUtils::DrawSprite( sprite, screen, { 10, 10 } );

    DrawUtils::Draw( screen );
    DrawUtils::Clear( screen, ' ' );

    // Rotation 3 (west)
    DrawUtils::RotateSprite( sprite );
    DrawUtils::DrawSprite( sprite, screen, { 10, 10 } );

    DrawUtils::Draw( screen );
    DrawUtils::Clear( screen, ' ' );

    // Rotation 4 (north)
    DrawUtils::RotateSprite( sprite );
    DrawUtils::DrawSprite( sprite, screen, { 10, 10 } );

    DrawUtils::Draw( screen );
}