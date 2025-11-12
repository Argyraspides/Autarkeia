#pragma once
#include "Entity.hpp"

class Ship : public Entity
{
  public:
    Ship();
    ~Ship() = default;

    void Rotate( int deg );
    void Move( Vec2I direction );
    const Sprite& GetSprite() const;
    Vec2I GetPosition() const;

  private:
    int m_rotation; // 0 degrees -> ship nose pointing vertically up
};