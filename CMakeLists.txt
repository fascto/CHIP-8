cmake_minimum_required(VERSION 3.16)
project(CHIP_8 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
add_subdirectory(vendored/SDL_image EXCLUDE_FROM_ALL)

add_executable(CHIP_8
        main.cpp
        main.h
)
target_link_libraries(CHIP_8 PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)

target_include_directories(CHIP_8 PRIVATE include)
