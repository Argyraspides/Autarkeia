cmake_minimum_required(VERSION 3.31)
set( CMAKE_CXX_STANDARD 17 )

message("Adding ${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory( common )
add_subdirectory( peripheral_detection )