#include "crosshair.h"

void Crosshair::Init() {
    toggled = true;
    texture.Init("res/images/crosshair.png", "tex", GL_RGBA, GL_RGBA);
}

void Crosshair::Render() {
    if (!toggled) {
        return;
    }

    UIComponent::shader.UniformTexture2D(texture, 0);

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

    UIComponent::ibo.Buffer(sizeof(indices), indices);
    UIComponent::vbo.Buffer(sizeof(vertices), vertices);

    UIComponent::vao.AttribPointer(UIComponent::vbo, 0, 2, GL_FLOAT, 4 * sizeof(float), 0 * sizeof(float));
    UIComponent::vao.AttribPointer(UIComponent::vbo, 1, 2, GL_FLOAT, 4 * sizeof(float), 2 * sizeof(float));

    UIComponent::vao.Bind();
    UIComponent::ibo.Bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
