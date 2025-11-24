#include "Asteroid.hpp"
#include "Vec2I.hpp"
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <limits>

// ARGYRASPIDES::OPTIMIZATION() { This fucking O(n^2) shit sucks ass think of a better way to do it
//  for now its fine tho because vertexCt shouldn't be too large (maybe 10 absolute max so we get 100 operations) }
Asteroid::Asteroid( size_t vertexCt )
    : Entity{}
{
    assert( vertexCt >= 3 && "A polygon needs 3 or more sides you moron" );

    // Algorithm: Determine the geometric center of the point cloud
    // Draw a bunch of vectors from the geometric center to each of the points in the point cloud
    // If we then iterate through these vectors in a circular fashion, we will always end up with a
    // closed polygon.
    //
    // To find the right order, create multiple points on a circle, and find the closest
    // point from that circle to a point in the point cloud. That will be the next point to draw a line to

    constexpr int minimumXVertex = 25;
    constexpr int randXVertexRange = 25;
    constexpr int maxXVertex = minimumXVertex + randXVertexRange;

    constexpr int minimumYVertex = 25;
    constexpr int randYVertexRange = 25;
    constexpr int maxYVertex = minimumYVertex + randYVertexRange;

    auto GenerateRandomVertex = [ & ]() -> Vec2I {
        srand( std::chrono::system_clock::now().time_since_epoch().count() );
        int randX = ( rand() % randXVertexRange ) + minimumXVertex;
        int randY = ( rand() % randYVertexRange ) + minimumYVertex;

        constexpr int asteroidSizeScalar = 3;
        return Vec2I{ randX, randY } * asteroidSizeScalar;
    };

    // Might contain duplicates zzz
    std::vector< Vec2I > asteroidVertices;
    Vec2I circleCenter;
    for ( int i = 0; i < vertexCt; i++ )
    {
        Vec2I randomVertex = GenerateRandomVertex();
        asteroidVertices.push_back( randomVertex );
        circleCenter = circleCenter + randomVertex;
    }
    circleCenter = circleCenter / vertexCt;

    float degreeIncrement = 360.0F / static_cast< float >( vertexCt );
    std::vector< Vec2I > circlePoints;
    for ( float deg = 0; deg <= 360; deg += degreeIncrement )
    {
        constexpr float DEG_TO_RAD = M_PI / 180;

        float x = std::cos( deg * DEG_TO_RAD ) * maxXVertex;
        float y = std::sin( deg * DEG_TO_RAD ) * maxYVertex;
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