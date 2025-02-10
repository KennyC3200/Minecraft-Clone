cmake_minimum_required(VERSION 3.5...3.11)
project(Minecraft)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(
    -g
    -Wall
    -Wextra
    -Werror
    -Wfloat-conversion
    -Wunused
    -Wunused-parameter
    -O3
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# Glad
add_subdirectory(lib/glad)
include_directories(PUBLIC lib/glad/include)

# GLFW
find_package(glfw3 REQUIRED)
include_directories(PUBLIC lib/glfw)

# GLM
find_package(glm CONFIG REQUIRED)
include_directories(PUBLIC lib/glm)

# stb image
include_directories(PUBLIC lib/stb)

# imgui
add_subdirectory(lib/imgui)
include_directories(
    PUBLIC lib/imgui
    PUBLIC lib/imgui/backends
    PUBLIC lib/glfw/include
)

# Fast Noise Lite
include_directories(PUBLIC lib/fast_noise_lite)

add_executable(Minecraft src/main.cpp)
add_subdirectory(src)
add_subdirectory(src/gfx)
add_subdirectory(src/input)
add_subdirectory(src/player)
add_subdirectory(src/ui/gui)
add_subdirectory(src/ui/hud)
add_subdirectory(src/util)
add_subdirectory(src/world)
target_link_libraries(Minecraft
    PUBLIC game
    PUBLIC gfx
    PUBLIC input
    PUBLIC player
    PUBLIC gui
    PUBLIC hud
    PUBLIC util
    PUBLIC world
)
