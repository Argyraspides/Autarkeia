cmake_minimum_required(VERSION 3.31)
project(Autarkeia)

set( CMAKE_CXX_STANDARD 17 )

set( DRAWING_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/drawing/include
)
file( GLOB DRAWING_SOURCE_CODE
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/drawing/include/*.hpp
)

add_executable(Autarkeia
    main.cpp
    ${DRAWING_SOURCE_CODE}
)

target_include_directories( Autarkeia PRIVATE
    ${DRAWING_INCLUDE_DIRS}
)
