#include "ui_component.h"

Shader UIComponent::shader;
VAO UIComponent::vao;
VBO UIComponent::vbo;
VBO UIComponent::ibo;
Window* UIComponent::window;

void UIComponent::Init(Window *window) {
    UIComponent::window = window;

    shader.Init("res/shaders/ui_2d.vs", "res/shaders/ui_2d.fs");
    vao.Init();
    vbo.Init(GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
    ibo.Init(GL_ELEMENT_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
}

void UIComponent::Destroy() {
    shader.Destroy();
    vao.Destroy();
    vbo.Destroy();
    ibo.Destroy();
}
