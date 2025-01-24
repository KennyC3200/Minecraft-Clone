#include "hud_component.h"

Window* HudComponent::window;
Shader HudComponent::shader;
VAO HudComponent::vao;
VBO HudComponent::vbo;
VBO HudComponent::ibo;

void HudComponent::Init(Window* window) {
    HudComponent::window = window;

    shader.Init("res/shaders/hud.vert", "res/shaders/hud.frag");
    vao.Init();
    vbo.Init(GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
    ibo.Init(GL_ELEMENT_ARRAY_BUFFER, GL_DYNAMIC_DRAW);

}

void HudComponent::Destroy() {
    shader.Destroy();
    vao.Destroy();
    vbo.Destroy();
    ibo.Destroy();
}
