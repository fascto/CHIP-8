cmake_minimum_required(VERSION 3.16)
project(CHIP_8 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
add_subdirectory(vendored/SDL_image EXCLUDE_FROM_ALL)

add_library(chip8_common STATIC
        ltexture.cpp
)
target_link_libraries(chip8_common PUBLIC SDL3::SDL3 SDL3_image::SDL3_image)
target_include_directories(chip8_common PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(CHIP_8
        main.cpp
)
target_link_libraries(CHIP_8 PRIVATE chip8_common)

add_executable(key_capture
        keys_capture.cpp
)
target_link_libraries(key_capture PRIVATE chip8_common)
