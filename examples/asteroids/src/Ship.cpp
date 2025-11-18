#include "Ship.hpp"
#include "DrawUtils.hpp"
#include "Vec2I.hpp"

Ship::Ship()
    : Entity{}
{
    int spaceShipDim = 11;
    Vec2I spaceShipHead = { spaceShipDim - 1, spaceShipDim / 2 };
    Vec2I spaceShipBase1 = { 0, 0 };
    Vec2I spaceShipBase2 = { 0, spaceShipDim - 1 };

    m_sprite = Sprite{ { spaceShipHead, spaceShipBase1, spaceShipBase2 } };
    m_position = { 0, 0 };
}
