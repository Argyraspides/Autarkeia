#include "Entity.hpp"

Entity::Entity()
{
}

void Entity::SetSprite( Sprite&& sprite )
{
    // I hate this. Even though Sprite&& is an r-value reference the C++
    // standard says that any named values are l-value types regardless of what the type says.
    // So we have to explicitly say "no really, please treat it like an r-value reference!".
    //
    // Bruh.
    m_sprite.emplace( std::move( sprite ) );
}