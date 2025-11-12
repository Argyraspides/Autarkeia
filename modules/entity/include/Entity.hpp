#include <optional>
#include "Sprite.hpp"

class Entity {
public:
    Entity();
    ~Entity() = default;

    void SetSprite( Sprite&& m_sprite );

protected:
    std::optional< Sprite > m_sprite;
    std::optional< Vec2I > m_position;
};