cmake_minimum_required( VERSION 3.28 )
set( CMAKE_CXX_STANDARD 20 )

message("Adding ${CMAKE_CURRENT_SOURCE_DIR}")

project( Math )

add_library( Math INTERFACE )

target_include_directories( Math INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)