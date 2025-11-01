#include "DrawUtils.hpp"
#include "Frame.hpp"
#include "ShipSprite.hpp"
#include <chrono>

Frame screen( 35, 35 );

int main()
{
    DrawUtils::Clear( screen, '.' );

    Sprite sprite( 10, 10 );
    DrawUtils::Clear( sprite.frame, DrawUtils::TRANSPARENT_CHAR );

    DrawUtils::QuickDrawTriangle( { 5, 0 }, { 0, 9 }, { 9, 9 }, sprite.frame, 'X' );
    DrawUtils::RotateSprite( sprite );

    DrawUtils::DrawSprite( sprite, screen, { 10, 10 } );
    DrawUtils::Draw( screen );
}