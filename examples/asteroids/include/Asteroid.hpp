#pragma once
#include "Entity.hpp"

class Asteroid : public Entity
{
  public:
    Asteroid( size_t sideCt = 3 );
    ~Asteroid() = default;
};