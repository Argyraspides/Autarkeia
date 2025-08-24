cmake_minimum_required(VERSION 3.31)

project( Autarkeia )

option( BUILD_TESTS "Builds Autarkeia tests" ON )

set( CMAKE_CXX_STANDARD 17 )

add_subdirectory( modules/drawing )

if( BUILD_TESTS )
    add_subdirectory( modules/catch2 )
    add_subdirectory( modules/drawing/test )
endif()

add_executable( Autarkeia
    main.cpp
)

target_link_libraries( Autarkeia PRIVATE
    Drawing
)
