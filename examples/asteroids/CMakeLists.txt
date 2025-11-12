project( Asteroids )

message("Adding ${CMAKE_CURRENT_SOURCE_DIR}")

set( ASTEROIDS_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ShipSprite.hpp
)
add_executable( Asteroids
    ${ASTEROIDS_SOURCES}
)

target_include_directories( Asteroids PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries( Asteroids PRIVATE
    Drawing
    InputCommon
)