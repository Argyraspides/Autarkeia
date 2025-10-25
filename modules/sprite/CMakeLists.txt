cmake_minimum_required( VERSION 3.28 )
set( CMAKE_CXX_STANDARD 20 )

project( Sprite )

message("Adding ${CMAKE_CURRENT_SOURCE_DIR}")

set( SPRITE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Sprite.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Sprite.cpp
)

add_library( Sprite
    ${SPRITE_SOURCES}
)

target_include_directories( Sprite
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries( Sprite
    PRIVATE Drawing
)