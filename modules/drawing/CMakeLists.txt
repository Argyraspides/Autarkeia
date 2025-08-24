cmake_minimum_required(VERSION 3.31)
set( CMAKE_CXX_STANDARD 17 )

project( Drawing )

set( DRAWING_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set ( DRAWING_SOURCE_CODE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/DrawUtils.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Vec2I.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/dummy.cpp # See dummy.cpp for why it's here
)

add_library( Drawing STATIC
    ${DRAWING_SOURCE_CODE}
)

target_include_directories( Drawing PUBLIC
    ${DRAWING_INCLUDE_DIRS}
)