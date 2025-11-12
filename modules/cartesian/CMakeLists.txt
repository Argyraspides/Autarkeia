cmake_minimum_required( VERSION 3.28 )
set( CMAKE_CXX_STANDARD 20 )

message("Adding ${CMAKE_CURRENT_SOURCE_DIR}")

project( Cartesian )

add_library( Cartesian INTERFACE )

target_include_directories( Cartesian INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries( Cartesian INTERFACE 
    Math
)