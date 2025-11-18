//
// Created by Argyraspides on 8/23/25.
//
#pragma once

#include "Matf.hpp"
#include <cstdint>
#include <cstring>
#include <cwchar>

struct Vec2F;
struct Vec2I
{
    int x, y;

    Vec2I();
    Vec2I( int x, int y );
    Vec2I( Vec2F other );

    Vec2I operator+( Vec2I other ) const;
    Vec2I operator-( Vec2I other ) const;
    void operator+=( Vec2I other );
    Vec2I operator/( int other ) const;
    Vec2I operator*( int other ) const;
    Vec2I operator*( Matf< 2, 2 > matrix2by2 ) const;
    void operator=( Vec2I other );
    bool operator==( Vec2I other ) const;
    bool IsAbove(Vec2I other);
    bool IsBelow(Vec2I other);
    bool IsLeftOf(Vec2I other);
    bool IsRightOf(Vec2I other);

};

const inline Vec2I VEC2I_UP = Vec2I{ 0, -1 };
const inline Vec2I VEC2I_DOWN = Vec2I{ 0, 1 };
const inline Vec2I VEC2I_LEFT = Vec2I{ -1, 0 };
const inline Vec2I VEC2I_RIGHT = Vec2I{ 1, 0 };

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
    bool operator()( const Vec2I& first, const Vec2I& second ) const
    {
        return first.x == second.x && first.y == second.y;
    }
};
