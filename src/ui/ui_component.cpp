#include "ui_component.h"

Shader UIComponent::shader;
VAO UIComponent::vao;
VBO UIComponent::vbo;
VBO UIComponent::ibo;
Window *UIComponent::window;

void UIComponent::init(Window *window) {
    UIComponent::window = window;

    shader.init("res/shaders/ui_2d.vs", "res/shaders/ui_2d.fs");
    vao.init();
    vbo.init(GL_ARRAY_BUFFER, DYNAMIC_DRAW);
    ibo.init(GL_ELEMENT_ARRAY_BUFFER, DYNAMIC_DRAW);
}

void UIComponent::destroy() {
    shader.destroy();
    vao.destroy();
    vbo.destroy();
    ibo.destroy();
}
