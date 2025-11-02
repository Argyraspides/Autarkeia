//
// Created by Argyraspides on 8/23/25.
//

#ifndef VEC2I_HPP
#define VEC2I_HPP

#include <cstdint>
#include <cstring>
#include <cwchar>
#include "Matf.hpp"

struct Vec2I
{
    int x, y;

    Vec2I()
        : x( 0 ),
          y( 0 )
    {
    }

    constexpr Vec2I( int x, int y )
        : x( x ),
          y( y )
    {
    }

    Vec2I operator+( Vec2I other ) const
    {
        return { x + other.x, y + other.y };
    }

    Vec2I operator-( Vec2I other ) const
    {
        return { x - other.x, y - other.y };
    }

    void operator+=( Vec2I other )
    {
        x += other.x;
        y += other.y;
    }

    Vec2I operator/( int other ) const
    {
        return { x / other, y / other };
    }

    Vec2I operator*( int other ) const
    {
        return { x * other, y * other };
    }

    Vec2I operator*( Matf<2, 2> matrix2by2 ) const
    {
        std::pair<float, float > iHat = { matrix2by2.At(0, 0), matrix2by2.At(1, 0) };
        std::pair<float, float > jHat = { matrix2by2.At(0, 1), matrix2by2.At(1, 1) };

        Vec2I iHatScaled = { static_cast < int > ( iHat.first * x ), static_cast< int > ( iHat.second * x ) };
        Vec2I jHatScaled = { static_cast < int > ( jHat.first * y ), static_cast< int > ( jHat.second * y ) };

        return iHatScaled + jHatScaled;
    }

    void operator=( Vec2I other )
    {
        x = other.x;
        y = other.y;
    }

    bool operator==( Vec2I other ) const
    {
        return ( x == other.x ) & ( y == other.y );
    }
};

const Vec2I VEC2I_UP = Vec2I{ 0, -1 };
const Vec2I VEC2I_DOWN = Vec2I{ 0, 1 };
const Vec2I VEC2I_LEFT = Vec2I{ -1, 0 };
const Vec2I VEC2I_RIGHT = Vec2I{ 1, 0 };

struct Vec2IHash
{
    size_t operator()( const Vec2I& vec ) const
    {
        uint32_t x_t = static_cast< uint32_t >( vec.x );
        uint32_t y_t = static_cast< uint32_t >( vec.y );
        return ( static_cast< uint64_t >( x_t ) << 32 ) | y_t;
    }
};

struct Vec2IEquality
{
    bool operator()( const Vec2I& x, const Vec2I& y ) const
    {
        return x == y;
    }
};

#endif // VEC2I_HPP
