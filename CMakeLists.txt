cmake_minimum_required(VERSION 3.31)

project( Autarkeia )

option( BUILD_TESTS "Builds Autarkeia tests" ON )
option( BUILD_EXAMPLE_DVD "Builds bouncing DVD thingy example" ON )
option( BUILD_EXAMPLE_MOVING_BALL "Builds moving ball example, keyboard inputs n shit" ON )
option( BUILD_EXAMPLE_SNAKE "Builds snake example (literally just a game of snake)" ON )

set( CMAKE_CXX_STANDARD 20 )

add_subdirectory( modules/drawing )
add_subdirectory( modules/input )
add_subdirectory( modules/sprite )

if( BUILD_TESTS )
    add_subdirectory( modules/catch2 )
    add_subdirectory( modules/drawing/test )
endif()

if( BUILD_EXAMPLE_DVD )
    add_subdirectory( examples/dvd )
endif()

if( BUILD_EXAMPLE_MOVING_BALL )
    add_subdirectory( examples/moving_ball )
endif()

if( BUILD_EXAMPLE_SNAKE )
    add_subdirectory( examples/snake )
endif()

add_executable( Autarkeia
    main.cpp
)

target_link_libraries( Autarkeia PRIVATE
    Drawing
    InputCommon
    PeripheralDetector
    Sprite
)
