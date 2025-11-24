project( Asteroids )

message("Adding ${CMAKE_CURRENT_SOURCE_DIR}")

set( ASTEROIDS_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Ship.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Bullet.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Asteroid.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Game.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/AsteroidRenderers.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/AsteroidUpdates.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/AsteroidUtils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/AsteroidInputs.cpp
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
    Entity
)