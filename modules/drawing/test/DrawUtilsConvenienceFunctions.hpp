//
// Created by gaugamela on 8/31/25.
//

#ifndef DRAWUTILSCONVENIENCEFUNCTIONS_HPP
#define DRAWUTILSCONVENIENCEFUNCTIONS_HPP

#define DEFAULT_FRAMEBUF_CHAR '.'

#define DRAW_PIXEL( drawChar, gridSizeX, gridSizeY, px, py )                                                           \
    std::vector< std::vector< char > > grid( gridSizeY, std::vector< char >( gridSizeX, '.' ) );                       \
    Vec2I p = { px, py };                                                                                              \
    DrawUtils::DrawPixel( p, grid, drawChar );

#define CHECK_CLEAR( clearChar )                                                                                       \
    for ( const auto& row : grid )                                                                                     \
    {                                                                                                                  \
        for ( char cell : row )                                                                                        \
        {                                                                                                              \
            REQUIRE( cell == clearChar );                                                                              \
        }                                                                                                              \
    }

#define INITIALIZE_FRAMEBUF( gridSize )                                                                                 \
    std::vector< std::vector< char > > grid( gridSize.y, std::vector< char >( gridSize.x, '.' ) );

#endif // DRAWUTILSCONVENIENCEFUNCTIONS_HPP
