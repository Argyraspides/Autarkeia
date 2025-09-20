cmake_minimum_required( VERSION 3.31 )

project( MovingBall )

set( MOVING_BALL_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/MovingBall.cpp
)

add_executable( MovingBall
    ${MOVING_BALL_SOURCES}
)

target_link_libraries( MovingBall
    InputCommon
    Drawing
)