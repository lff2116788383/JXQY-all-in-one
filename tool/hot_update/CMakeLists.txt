cmake_minimum_required(VERSION 3.10)

project("hot_update")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_RPATH_USE_ORIGIN TRUE)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_FLAGS "-O2 -std=c++17 -pthread -DNDEBUG -D__LINUX__ -DUSE_FFMPEG4 -DLUA_USE_LINUX")

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/
)



file( GLOB source_files
        ${CMAKE_CURRENT_SOURCE_DIR}/*
)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/)

add_executable( hot_update ${source_files} )


target_link_libraries(hot_update
        curl
)


