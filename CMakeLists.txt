cmake_minimum_required(VERSION 3.29)
project(Klefki C)
find_library(CORE_GRAPHICS_FRAMEWORK CoreGraphics)
find_library(CORE_FOUNDATION_FRAMEWORK CoreFoundation)
set(CMAKE_C_STANDARD 11)

add_executable(Klefki main.c
        hotkeys.c
        constants.h
        klefkiAscii.h)
target_link_libraries(Klefki
        ${CORE_GRAPHICS_FRAMEWORK}
        ${CORE_FOUNDATION_FRAMEWORK})