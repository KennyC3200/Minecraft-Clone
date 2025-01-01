#pragma once

#include "hud_component.h"

class Crosshair : public HudComponent {
public:
    void Init();

    void Mesh() override {
        float x = window->GetPixelUnit().x * 14.0f;
        float y = window->GetPixelUnit().y * 14.0f;

        vertices.clear();
        vertices = {
             x,  y,  1.0f, 1.0f,
             x, -y,  1.0f, 0.0f,
            -x, -y,  0.0f, 0.0f,
            -x,  y,  0.0f, 1.0f,
        };

        indices.clear();
        indices = {
            0, 1, 3,
            1, 2, 3,
        };
    }

    void Render() override {
        if (!toggled) {
            return;
        }

        shader.UniformTexture2D(texture, 0);

        ibo.Buffer(indices.size() * sizeof(unsigned int), &indices[0]);
        vbo.Buffer(vertices.size() * sizeof(float), &vertices[0]);

        vao.AttribPointer(vbo, 0, 2, GL_FLOAT, 4 * sizeof(float), 0 * sizeof(float));
        vao.AttribPointer(vbo, 1, 2, GL_FLOAT, 4 * sizeof(float), 2 * sizeof(float));

        vao.Bind();
        ibo.Bind();

        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    }

private:
    Texture texture;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;
};
