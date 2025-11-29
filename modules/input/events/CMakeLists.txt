cmake_minimum_required( VERSION 3.28 )

set( EVENT_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include )

add_library( Events INTERFACE )

target_include_directories( Events INTERFACE 
    ${EVENT_INCLUDE_DIRS}
)