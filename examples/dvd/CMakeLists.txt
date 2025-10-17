cmake_minimum_required(VERSION 3.31)

message("Adding ${CMAKE_CURRENT_SOURCE_DIR} ...")

project( DVD )

set( CMAKE_CXX_STANDARD 20 )

add_executable( DVD
    DVD.cpp
)

target_link_libraries( DVD PRIVATE
    Drawing
)