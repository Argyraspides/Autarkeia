#include "Entity.hpp"
#include "DrawUtils.hpp"

Entity::Entity()
    : m_position{ 0, 0 },
      m_sprite{},
      m_rotation{ 0 }
{
}

void Entity::SetSprite( Sprite&& sprite )
{
    // I hate this. Even though Sprite&& is an r-value reference the C++
    // standard says that any named values are l-value types regardless of what the type says.
    // So we have to explicitly say "no really, please treat it like an r-value reference!".
    //
    // Bruh.
    m_sprite = std::move( sprite );
}

void Entity::SetSprite( const Sprite& sprite )
{
    m_sprite = sprite;
}

Sprite& Entity::GetSprite()
{
    return m_sprite;
}

void Entity::SetPosition( Vec2F position )
{
    m_position = position;
}

Vec2F Entity::GetPosition() const
{
    return m_position;
}

void Entity::SetVelocity( Vec2F velocity )
{
    m_velocity = velocity;
}

Vec2F Entity::GetVelocity() const
{
    return m_velocity;
}

void Entity::Move( Vec2F vector )
{
    m_position = m_position + vector;
}

void Entity::Rotate( int deg )
{
    DrawUtils::RotateSprite( m_sprite, deg );
    m_rotation = deg;
}

int Entity::GetRotation() const
{
    return m_rotation;
}
