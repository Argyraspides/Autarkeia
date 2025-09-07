cmake_minimum_required(VERSION 3.31)

project( Autarkeia )

option( BUILD_TESTS "Builds Autarkeia tests" ON )
option( BUILD_EXAMPLE_DVD "Builds bouncing DVD thingy example" ON )

set( CMAKE_CXX_STANDARD 17 )

add_subdirectory( modules/drawing )

if( BUILD_TESTS )
    add_subdirectory( modules/catch2 )
    add_subdirectory( modules/drawing/test )
endif()

if( BUILD_EXAMPLE_DVD )
    add_subdirectory( examples/dvd )
endif()

add_executable( Autarkeia
    main.cpp
)

target_link_libraries( Autarkeia PRIVATE
    Drawing
)
