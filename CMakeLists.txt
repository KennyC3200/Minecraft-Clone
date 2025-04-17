cmake_minimum_required(VERSION 3.5...3.11)
project(minecraft)

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
    -O2
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# Glad
add_library(glad STATIC lib/glad/src/glad.c)
include_directories(PUBLIC lib/glad/include)

# GLFW
find_package(glfw3 REQUIRED)
include_directories(PUBLIC lib/glfw/include)

# GLM
find_package(glm CONFIG REQUIRED)
include_directories(PUBLIC lib/glm)

# stb image
include_directories(INTERFACE lib/stb)

# imgui
add_library(imgui STATIC
    lib/imgui/imgui.cpp
    lib/imgui/imgui_demo.cpp
    lib/imgui/imgui_draw.cpp
    lib/imgui/imgui_tables.cpp
    lib/imgui/imgui_widgets.cpp
)
target_include_directories(imgui
    PUBLIC lib/imgui/backends
    PUBLIC lib/glfw/include
)
add_library(imgui_backends STATIC
    lib/imgui/backends/imgui_impl_glfw.cpp
    lib/imgui/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui_backends
    PUBLIC lib/imgui
    PUBLIC lib/glfw/include
)
target_link_libraries(imgui PUBLIC imgui_backends)
include_directories(
    PUBLIC lib/imgui
    PUBLIC lib/imgui/backends
)

# Fast Noise Lite
include_directories(INTERFACE lib/fast_noise_lite)

add_executable(minecraft src/main.cpp)
add_subdirectory(src)
add_subdirectory(src/gfx)
add_subdirectory(src/input)
add_subdirectory(src/player)
add_subdirectory(src/ui/gui)
add_subdirectory(src/ui/hud)
add_subdirectory(src/util)
add_subdirectory(src/world)
target_link_libraries(minecraft
    PRIVATE game
    PRIVATE gfx
    PRIVATE input
    PRIVATE player
    PRIVATE gui
    PRIVATE hud
    PRIVATE util
    PRIVATE world
)

add_custom_target(Run
    COMMAND ./minecraft
    DEPENDS minecraft
    COMMENT Running minecraft
)
