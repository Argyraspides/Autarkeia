cmake_minimum_required( VERSION 3.31 )
project( Snake )

message("Adding examples/snake ...")

set( SNAKE_SOURCES
   ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

add_executable( Snake
    ${SNAKE_SOURCES}
)

target_link_libraries( Snake
    InputCommon
    Drawing
)