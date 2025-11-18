//
// Created by Argyraspides on 8/23/25.
//
#include "Vec2I.hpp"
#include "Matf.hpp"
#include "Vec2F.hpp"
#include <cstring>
#include <cwchar>
#include <utility>

Vec2I::Vec2I()
    : x( 0 ),
      y( 0 )
{
}

Vec2I::Vec2I( int x, int y )
    : x( x ),
      y( y )
{
}

Vec2I::Vec2I( Vec2F other )
    : x( static_cast< int >( other.x ) ),
      y( static_cast< int >( other.y ) )
{
}

Vec2I Vec2I::operator+( Vec2I other ) const
{
    return { x + other.x, y + other.y };
}

Vec2I Vec2I::operator-( Vec2I other ) const
{
    return { x - other.x, y - other.y };
}

void Vec2I::operator+=( Vec2I other )
{
    x += other.x;
    y += other.y;
}

Vec2I Vec2I::operator/( int other ) const
{
    return { x / other, y / other };
}

Vec2I Vec2I::operator*( int other ) const
{
    return { x * other, y * other };
}

Vec2I Vec2I::operator*( Matf< 2, 2 > matrix2by2 ) const
{
    std::pair< float, float > iHat = { matrix2by2.At( 0, 0 ), matrix2by2.At( 1, 0 ) };
    std::pair< float, float > jHat = { matrix2by2.At( 0, 1 ), matrix2by2.At( 1, 1 ) };

    Vec2I iHatScaled = { static_cast< int >( iHat.first * x ), static_cast< int >( iHat.second * x ) };
    Vec2I jHatScaled = { static_cast< int >( jHat.first * y ), static_cast< int >( jHat.second * y ) };

    return iHatScaled + jHatScaled;
}

void Vec2I::operator=( Vec2I other )
{
    x = other.x;
    y = other.y;
}

bool Vec2I::operator==( Vec2I other ) const
{
    return ( x == other.x ) & ( y == other.y );
}

bool Vec2I::IsAbove( Vec2I other )
{
    return y < other.y;
}

bool Vec2I::IsBelow( Vec2I other )
{
    return !IsAbove( other );
}

bool Vec2I::IsLeftOf( Vec2I other )
{
    return x < other.x;
}

bool Vec2I::IsRightOf( Vec2I other )
{
    return !IsLeftOf( other );
}