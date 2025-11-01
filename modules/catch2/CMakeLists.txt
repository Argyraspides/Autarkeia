cmake_minimum_required(VERSION 3.28)

project( Catch2 )

set( CMAKE_CXX_STANDARD 20 )

message("Adding ${CMAKE_CURRENT_SOURCE_DIR}")

set( CATCH2_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set( CATCH2_SOURCE_CODE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/catch_amalgamated.cpp
)

add_library( Catch2
    ${CATCH2_SOURCE_CODE}
)

target_include_directories( Catch2 PUBLIC
    ${CATCH2_INCLUDE_DIRS}
)