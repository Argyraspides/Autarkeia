cmake_minimum_required(VERSION 3.31)

project( DrawingTests )

set( CMAKE_CXX_STANDARD 17 )

message("Adding ${CMAKE_CURRENT_SOURCE_DIR} ... ")

set( DRAWING_TEST_SOURCE_CODE
    CatchConfig.cpp
    DrawUtilsConvenienceFunctions.hpp
    DrawUtilsPixelTests.cpp
    DrawUtilsClearTests.cpp
    DrawUtilsDrawLineTests.cpp
)

add_executable( DrawingTests
    ${DRAWING_TEST_SOURCE_CODE}
)

target_link_libraries( DrawingTests PRIVATE
    Catch2
    Drawing
)