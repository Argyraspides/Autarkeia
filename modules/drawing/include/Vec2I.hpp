//
// Created by gaugamela on 8/23/25.
//

#ifndef VEC2I_HPP
#define VEC2I_HPP

struct Vec2I
{
    int x, y;

    Vec2I operator+( const Vec2I& other ) const
    {
        return { x + other.x, y + other.y };
    }

    void operator=( const Vec2I& other )
    {
        x = other.x;
        y = other.y;
    }
};

#endif // VEC2I_HPP
