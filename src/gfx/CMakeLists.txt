add_library(gfx STATIC
    renderer.cpp
    shader.cpp
    sprite_atlas.cpp
    texture.cpp
    vao.cpp
    vbo.cpp
    window.cpp
)
target_link_libraries(gfx
    glm::glm
    glfw
    glad
    imgui
)
