project( TextDrawing )

set( CXX_STANDARD_REQUIRED 20 )

set( TEXT_DRAWING_SOURCES main.cpp )

set( CMAKE_BUILD_TYPE Debug )

add_executable( TextDrawing ${TEXT_DRAWING_SOURCES})

target_link_libraries( TextDrawing PRIVATE Drawing )