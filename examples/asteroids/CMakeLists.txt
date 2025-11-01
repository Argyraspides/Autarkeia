project( Asteroids )

message("Adding ${CMAKE_CURRENT_SOURCE_DIR}")

add_executable( Asteroids
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

target_include_directories( Asteroids PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries( Asteroids PRIVATE
    Drawing
)