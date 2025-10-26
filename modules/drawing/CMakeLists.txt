cmake_minimum_required(VERSION 3.28)
set( CMAKE_CXX_STANDARD 20 )

message("Adding ${CMAKE_CURRENT_SOURCE_DIR}")

project( Drawing )

set( DRAWING_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set ( DRAWING_SOURCE_CODE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/DrawUtils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TextDrawUtils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Vec2I.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Frame.cpp
)

add_library( Drawing STATIC
    ${DRAWING_SOURCE_CODE}
)

target_include_directories( Drawing PUBLIC
    ${DRAWING_INCLUDE_DIRS}
)

target_link_libraries( Drawing
    PRIVATE Sprite
)