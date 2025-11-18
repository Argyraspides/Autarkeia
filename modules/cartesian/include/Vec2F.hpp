//
// Created by Argyraspides on 8/23/25.
//
#pragma once

#include "Matf.hpp"

struct Vec2I;
struct Vec2F
{
    float x, y;

    Vec2F();
    Vec2F( float x, float y );
    Vec2F( Vec2I other );

    Vec2F operator+( Vec2F other ) const;
    Vec2F operator-( Vec2F other ) const;
    void operator+=( Vec2F other );
    Vec2F operator/( float other ) const;
    Vec2F operator*( float other ) const;
    Vec2F operator*( Matf< 2, 2 > matrix2by2 ) const;

    void operator=( Vec2F other );

    bool operator==( Vec2F other ) const;
};

const inline Vec2F VEC2F_UP = Vec2F{ 0, -1 };
const inline Vec2F VEC2F_DOWN = Vec2F{ 0, 1 };
const inline Vec2F VEC2F_LEFT = Vec2F{ -1, 0 };
const inline Vec2F VEC2F_RIGHT = Vec2F{ 1, 0 };
