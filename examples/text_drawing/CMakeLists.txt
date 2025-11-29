project( TextDrawing )

set( CXX_STANDARD_REQUIRED 20 )

set( TEXT_DRAWING_SOURCES main.cpp )

add_executable( TextDrawing ${TEXT_DRAWING_SOURCES})

target_link_libraries( TextDrawing PRIVATE Drawing )