cmake_minimum_required( VERSION 3.28 )
set( CMAKE_CXX_STANDARD 20 )
project( Snake )

message("Adding ${CMAKE_CURRENT_SOURCE_DIR}...")

set( SNAKE_SOURCES
   ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

add_executable( Snake
    ${SNAKE_SOURCES}
)

target_link_libraries( Snake PRIVATE
    InputCommon
    Drawing
)