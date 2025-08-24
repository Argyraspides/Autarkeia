cmake_minimum_required(VERSION 3.31)
project( Autarkeia )

set( CMAKE_CXX_STANDARD 17 )

add_subdirectory( modules/drawing )

add_executable( Autarkeia
    main.cpp
)

target_link_libraries( Autarkeia PRIVATE
    Drawing
)
