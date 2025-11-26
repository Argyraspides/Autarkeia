cmake_minimum_required( VERSION 3.28 )
set( CMAKE_CXX_STANDARD 20 )

message("Adding ${CMAKE_CURRENT_SOURCE_DIR}")

project( Cartesian )

add_library( Cartesian 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Vec2F.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Vec2I.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GeoUtils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/LineI.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Polygon.cpp
)

target_include_directories( Cartesian PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries( Cartesian PUBLIC 
    Math
)