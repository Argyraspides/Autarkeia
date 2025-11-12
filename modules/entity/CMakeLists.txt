project( Entity )

set( CMAKE_CXX_STANDARD 20 )

message("Adding ${CMAKE_CURRENT_SOURCE_DIR}")

set( ENTITY_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Entity.cpp
)

add_library( Entity 
    ${ENTITY_SOURCES}
)

target_include_directories( Entity PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries( Entity PRIVATE
    Sprite
)