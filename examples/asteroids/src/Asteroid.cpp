#include "Asteroid.hpp"
#include "Vec2I.hpp"
#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <stdlib.h>
#include <unordered_set>

Asteroid::Asteroid()
    : Entity{}
{
    int randVertexCount = ( rand() % 6 ) + 3;

    auto GenerateRandomVertex = []() -> Vec2I {
        srand( std::chrono::system_clock::now().time_since_epoch().count() );
        int randX = ( rand() % 25 ) + 20;
        int randY = ( rand() % 25 ) + 20;
        Vec2I randPos = { randX, randY };
        randPos = randPos * 3;
        return randPos;
    };

    std::unordered_set< Vec2I, Vec2IHash, Vec2IEquality > asteroidVertices;
    int circleStartX, circleEndY;
    circleStartX = circleEndY = std::numeric_limits< int >::max();

    int circleEndX, circleStartY;
    circleEndX = circleStartY = std::numeric_limits< int >::min();

    for ( int i = 0; i < randVertexCount; i++ )
    {
        Vec2I randomVertex = GenerateRandomVertex();

        circleStartX = std::min( randomVertex.x, circleStartX );
        circleEndY = std::min( randomVertex.y, circleEndY );

        circleEndX = std::max( randomVertex.x, circleEndX );
        circleStartY = std::max( randomVertex.y, circleStartY );

        asteroidVertices.insert( randomVertex );
    }

    Vec2I circleCenter = { ( circleStartX + circleEndX ) / 2, ( circleStartY + circleEndY ) / 2 };

    std::vector< std::pair< Vec2I, Vec2I > > asteroidVectors;
    for ( auto it = asteroidVertices.begin(); it != asteroidVertices.end(); ++it )
    {
        const Vec2I asteroidVertex = *it;
        Vec2I circleVec = asteroidVertex - circleCenter;
        asteroidVectors.push_back( { circleVec, asteroidVertex } );
    }

    // Final vertices in order of drawing that will result in a closed polygon
    std::vector< Vec2I > finalVertices;
    for ( auto& [ circleVeci, asteroidVertexi ] : asteroidVectors )
    {
        std::pair< Vec2I, Vec2I > next;
        int closestToOne = std::numeric_limits< int >::max();
        for ( auto& [ circleVecj, asteroidVertexj ] : asteroidVectors )
        {
            int distFromOne = abs( circleVeci.DotProd( circleVecj ) - 1 );

            if ( distFromOne < closestToOne )
            {
                next = { circleVecj, asteroidVertexj };
                closestToOne = distFromOne;
            }
        }
        finalVertices.push_back( next.second );

        auto removes = std::remove_if( asteroidVectors.begin(), asteroidVectors.end(),
                                       [ next ]( std::pair< Vec2I, Vec2I > p ) { return p == next; } );
        asteroidVectors.erase( removes, asteroidVectors.end() );
    }

    finalVertices.push_back( asteroidVectors.front().second );
    SetSprite( Sprite{ finalVertices } );
}