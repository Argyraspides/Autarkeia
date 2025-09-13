cmake_minimum_required(VERSION 3.31)
set( CMAKE_CXX_STANDARD 17 )

message("Adding ${CMAKE_CURRENT_SOURCE_DIR}")

project( PeripheralDetector )

set( PERIPHERAL_DETECTION_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/PeripheralDetector.hpp
)

add_library( PeripheralDetector
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PeripheralDetector.cpp
)

target_include_directories( PeripheralDetector PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries( PeripheralDetector
    InputCommon
)
