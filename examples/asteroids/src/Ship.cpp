#include "Ship.hpp"
#include "DrawUtils.hpp"

static Vec2I spaceShipHead = { 11 / 2, 0 };
static Vec2I spaceShipBase1 = { 0, 10 };
static Vec2I spaceShipBase2 = { 10, 10 };

static Sprite spaceShip{ { spaceShipHead, spaceShipBase1, spaceShipBase2 } };

Ship::Ship()
    : Entity{}
{
    m_sprite.emplace( Sprite{ { spaceShipHead, spaceShipBase1, spaceShipBase2 } } );
    assert( m_sprite.has_value() && "Ship must have sprite" );

    m_position = { 0, 0 };
    assert( m_position.has_value() && "Ship must have a position" );
}

void Ship::Rotate( int deg )
{
    DrawUtils::RotateSprite( *m_sprite, deg );
}

void Ship::Move( Vec2I offset )
{
    *m_position += offset;
}

const Sprite& Ship::GetSprite() const
{
    return m_sprite.value();
}

Vec2I Ship::GetPosition() const
{
    return m_position.value();
}