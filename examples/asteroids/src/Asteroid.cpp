#include "Asteroid.hpp"
#include "Vec2I.hpp"
#include <array>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <set>
#include <stdlib.h>

Asteroid::Asteroid()
    : Entity{}
{
    int randVertexCount = ( rand() % 6 ) + 3;

    std::set< Vec2I, Vec2IEquality > disconnectedVertices;
    std::set< Vec2I, Vec2IEquality > connectedVertices;

    auto GenerateRandomVertex = []() -> Vec2I {
        srand( std::chrono::system_clock::now().time_since_epoch().count() );
        int randX = ( rand() % 25 ) + 20;
        int randY = ( rand() % 25 ) + 20;
        Vec2I randPos = { randX, randY };
        return randPos;
    };

    for ( int i = 0; i < randVertexCount; i++ )
    {
        Vec2I randomVec =  GenerateRandomVertex() ;
        disconnectedVertices.insert(randomVec);
    }

    std::array< Vec2I, 4 > directions = { VEC2I_RIGHT, VEC2I_DOWN, VEC2I_LEFT, VEC2I_UP };
    enum Direction
    {
        RIGHT,
        DOWN,
        LEFT,
        UP
    };
    Direction currentDirectionIdx = Direction::RIGHT;

    Vec2I lastConnectedPoint = GenerateRandomVertex();
    connectedVertices.insert( lastConnectedPoint );
    std::vector< Vec2I > finalPtOrder;
    while ( !disconnectedVertices.empty() )
    {
        Vec2I closestNextPoint;
        int minDist = std::numeric_limits< int >::max();
        bool foundClosestPoint = false;
        for ( Vec2I vertex : disconnectedVertices )
        {
            Vec2I connectedToDisconnected = vertex - lastConnectedPoint;
            int dist = std::abs( std::hypot( connectedToDisconnected.x, connectedToDisconnected.y ) );
            if ( dist < minDist )
            {
                switch ( currentDirectionIdx )
                {
                case RIGHT:
                    if ( !vertex.IsRightOf( lastConnectedPoint ) )
                        continue;
                case DOWN:
                    if ( !vertex.IsBelow( lastConnectedPoint ) )
                        continue;
                case LEFT:
                    if ( !vertex.IsLeftOf( lastConnectedPoint ) )
                        continue;
                case UP:
                    if ( !vertex.IsAbove( lastConnectedPoint ) )
                        continue;
                }

                closestNextPoint = vertex;
                foundClosestPoint = true;
            }
        }

        if ( !foundClosestPoint )
        {
            currentDirectionIdx = static_cast< Direction >( currentDirectionIdx + 1 );
        }
        else
        {
            disconnectedVertices.erase( closestNextPoint );
            connectedVertices.insert( closestNextPoint );
            finalPtOrder.push_back( closestNextPoint );
        }

        SetSprite( Sprite{ finalPtOrder } );
    }
}