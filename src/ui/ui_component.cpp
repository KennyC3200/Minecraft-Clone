#include "ui_component.hpp"

Shader UIComponent::shader;
Texture UIComponent::textures[UI_TEXTURE_LAST];
VAO UIComponent::vao;
VBO UIComponent::vbo;
VBO UIComponent::ibo;
Window *UIComponent::window;

void UIComponent::init(Window *window) {
    UIComponent::window = window;

    textures[UI_TEXTURE_CROSSHAIR] = Texture::create("res/images/crosshair.png", "tex", GL_RGBA, GL_RGBA);

    shader.init("res/shaders/ui_2d.vs", "res/shaders/ui_2d.fs");
    vao.init();
    vbo.init(GL_ARRAY_BUFFER, DYNAMIC_DRAW);
    ibo.init(GL_ELEMENT_ARRAY_BUFFER, DYNAMIC_DRAW);
}

void UIComponent::destroy() {
    for (size_t i = 0; i < UI_TEXTURE_LAST; i++) {
        textures[i].destroy();
    }

    shader.destroy();
    vao.destroy();
    vbo.destroy();
    ibo.destroy();
}

void UIComponent::init() {
}

void UIComponent::render() {
}
