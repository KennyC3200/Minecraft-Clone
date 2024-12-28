#include "crosshair.hpp"

void Crosshair::init() {
    toggled = true;
    texture.init("res/images/crosshair.png", "tex", GL_RGBA, GL_RGBA);
}

void Crosshair::render() {
    if (!toggled) {
        return;
    }

    UIComponent::shader.uniform_texture_2d(texture, 0);

    float x = window->size.y / 1000.0f * 0.01f,
          y = window->size.x / 1000.0f * 0.01f;

    float vertices[] = {
         x,  y,  1.0f, 1.0f,
         x, -y,  1.0f, 0.0f,
        -x, -y,  0.0f, 0.0f,
        -x,  y,  0.0f, 1.0f,
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3,
    };

    UIComponent::ibo.buffer(sizeof(indices), indices);
    UIComponent::vbo.buffer(sizeof(vertices), vertices);

    UIComponent::vao.attr(UIComponent::vbo, 0, 2, GL_FLOAT, 4 * sizeof(float), 0 * sizeof(float));
    UIComponent::vao.attr(UIComponent::vbo, 1, 2, GL_FLOAT, 4 * sizeof(float), 2 * sizeof(float));

    UIComponent::vao.bind();
    UIComponent::ibo.bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
