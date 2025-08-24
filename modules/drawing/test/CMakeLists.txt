cmake_minimum_required(VERSION 3.31)

project( DrawingTests )

set( CMAKE_CXX_STANDARD 17 )


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../catch2
        ${CMAKE_CURRENT_BINARY_DIR}/catch2)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../drawing
        ${CMAKE_CURRENT_BINARY_DIR}/drawing)

set( DRAWING_TEST_SOURCE_CODE
    DrawUtilsTest.cpp
)

add_executable( DrawingTests
    ${DRAWING_TEST_SOURCE_CODE}
)

target_link_libraries( DrawingTests PRIVATE
    Catch2
    Drawing
)