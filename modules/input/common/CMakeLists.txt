cmake_minimum_required(VERSION 3.28)
set( CMAKE_CXX_STANDARD 20 )

message("Adding ${CMAKE_CURRENT_SOURCE_DIR}")

project( InputCommon )

set( INPUT_COMMON_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/KeyboardInputHandler.cpp
)

set( INPUT_COMMON_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KeyboardInfo.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KeyboardInputHandler.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/PeripheralInputException.hpp
)

add_library( InputCommon
    ${INPUT_COMMON_SOURCES}
    ${INPUT_COMMON_HEADERS}
)

target_include_directories( InputCommon PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries( InputCommon PRIVATE
    PeripheralDetector
)