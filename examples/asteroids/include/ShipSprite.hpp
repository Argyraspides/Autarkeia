#include "Sprite.hpp"

// Space ship is 11x11
static inline Vec2I spaceShipHead = { 11 / 2, 0 };
static inline Vec2I spaceShipBase1 = { 0, 10 };
static inline Vec2I spaceShipBase2 = { 10, 10 };

static inline Sprite spaceShip{ { spaceShipHead, spaceShipBase1, spaceShipBase2 } };