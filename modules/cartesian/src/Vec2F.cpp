//
// Created by Argyraspides on 8/23/25.
//
#include "Vec2F.hpp"
#include "Vec2I.hpp"
#include <math.h>

Vec2F::Vec2F()
    : x( 0 ),
      y( 0 )
{
}

Vec2F::Vec2F( float x, float y )
    : x( x ),
      y( y )
{
}

Vec2F::Vec2F( Vec2I other )
    : x( static_cast< float >( other.x ) ),
      y( static_cast< float >( other.y ) )
{
}

Vec2F Vec2F::operator+( Vec2F other ) const
{
    return { x + other.x, y + other.y };
}

Vec2F Vec2F::operator-( Vec2F other ) const
{
    return { x - other.x, y - other.y };
}

void Vec2F::operator+=( Vec2F other )
{
    x += other.x;
    y += other.y;
}

Vec2F Vec2F::operator/( float other ) const
{
    return { x / other, y / other };
}

Vec2F Vec2F::operator*( float other ) const
{
    return { x * other, y * other };
}

Vec2F Vec2F::operator*( Matf< 2, 2 > matrix2by2 ) const
{
    std::pair< float, float > iHat = { matrix2by2.At( 0, 0 ), matrix2by2.At( 1, 0 ) };
    std::pair< float, float > jHat = { matrix2by2.At( 0, 1 ), matrix2by2.At( 1, 1 ) };

    Vec2F iHatScaled = { iHat.first * x, iHat.second * x };
    Vec2F jHatScaled = { jHat.first * y, jHat.second * y };

    return iHatScaled + jHatScaled;
}

void Vec2F::operator=( Vec2F other )
{
    x = other.x;
    y = other.y;
}

bool Vec2F::operator==( Vec2F other ) const
{
    return ( x == other.x ) & ( y == other.y );
}

Vec2F Vec2F::Normalized() const
{
    // return ( *this ) / std::hypot( x, y );
    float div = std::hypot( x, y );
    return { x / div, y / div };
}