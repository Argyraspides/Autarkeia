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
    int randVertexCount = ( rand() % 6 ) + 10;

    auto GenerateRandomVertex = []() -> Vec2I {
        srand( std::chrono::system_clock::now().time_since_epoch().count() );
        int randX = ( rand() % 25 ) + 20;
        int randY = ( rand() % 25 ) + 20;
        Vec2I randPos = { randX, randY };
        randPos = randPos * 3;
        return randPos;
    };

    std::unordered_set< Vec2I, Vec2IHash, Vec2IEquality > asteroidVertices;
    Vec2I circleCenter;
    for ( int i = 0; i < randVertexCount; i++ )
    {
        Vec2I randomVertex = GenerateRandomVertex();
        asteroidVertices.insert( randomVertex );
        circleCenter = circleCenter + randomVertex;
    }
    circleCenter = circleCenter / randVertexCount;

    // Generate that circle based on number of points
    float degreeIncrement = 360.0F / static_cast< float >( randVertexCount );
    std::vector< Vec2I > circlePoints;
    for ( float deg = 0; deg <= 360; deg += degreeIncrement )
    {
        constexpr float DEG_TO_RAD = M_PI / 180;
        float x = std::cos( deg * DEG_TO_RAD ) * 45;
        float y = std::sin( deg * DEG_TO_RAD ) * 45;
        Vec2I finalPt = Vec2I( x, y ) + circleCenter;
        circlePoints.push_back( finalPt );
    }

    std::vector< Vec2I > finalPoints;
    for ( auto circlePt = circlePoints.begin(); circlePt != circlePoints.end(); ++circlePt )
    {
        Vec2I nextVertex;
        int minDist = std::numeric_limits< int >::max();
        for ( auto asteroidVertex = asteroidVertices.begin(); asteroidVertex != asteroidVertices.end();
              ++asteroidVertex )
        {
            int xDist = std::abs( ( *asteroidVertex ).x - ( *circlePt ).x );
            int yDist = std::abs( ( *asteroidVertex ).y - ( *circlePt ).y );
            int dist = std::hypot( xDist, yDist );
            if ( dist < minDist )
            {
                minDist = dist;
                nextVertex = *asteroidVertex;
            }
        }

        finalPoints.push_back( nextVertex );
    }

    SetSprite( Sprite{ finalPoints } );
}