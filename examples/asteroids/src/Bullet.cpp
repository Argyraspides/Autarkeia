
#include "Bullet.hpp"

Bullet::Bullet()
    : Entity{}
{
    m_sprite = std::move( Sprite{ { Vec2I{ 0, 0 } } } );
}