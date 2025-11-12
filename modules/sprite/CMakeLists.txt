project( Sprite )

set( CMAKE_CXX_STANDARD 20 )

set( SPRITE_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Sprite.cpp
)
add_library( Sprite 
    ${SPRITE_SOURCES}
)

target_include_directories( Sprite PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries( Sprite PUBLIC 
    Cartesian 
)