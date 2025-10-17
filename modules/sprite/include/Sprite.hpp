//
// Created by gaugamela on 9/28/25.
//

#ifndef SPRITE_HPP
#define SPRITE_HPP
#include "Vec2I.hpp"
#include <vector>
struct Sprite
{
  public:
    Sprite() = delete;
    ~Sprite();
    void AddPixel( Vec2I );
  private:
    std::vector<Vec2I> m_spritePixels;
};

#endif // SPRITE_HPP
