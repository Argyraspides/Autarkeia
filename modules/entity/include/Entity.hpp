#include <optional>
#include "Sprite.hpp"

class Entity {
public:
    Entity();
    ~Entity() = default;

private:
    std::optional< Sprite > m_sprite;
};