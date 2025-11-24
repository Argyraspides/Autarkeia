#pragma once
#include "Sprite.hpp"
#include "Vec2F.hpp" 

class Entity
{
  public:
    Entity();
    ~Entity() = default;

    void SetSprite( Sprite&& sprite );
    void SetSprite( const Sprite& sprite );
    const Sprite& GetSprite() const;

    void SetPosition( Vec2F position );
    Vec2F GetPosition() const;

    void SetVelocity( Vec2F velocity );
    Vec2F GetVelocity() const;

    void Move( Vec2F vector );

    void Rotate( int deg );
    int GetRotation() const;

  protected:
    Sprite m_sprite;
    int m_rotation;

    Vec2F m_position;
    Vec2F m_velocity;
};