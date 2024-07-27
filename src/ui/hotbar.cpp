#include "hotbar.hpp"

void Hotbar::init(Player *player) {
    this->player = player;

    toggled = true;
    atlas = SpriteAtlas("res/images/hotbar.png", "tex", {22, 22});
}

void Hotbar::render() {
    if (!toggled) {
        return;
    }

    UIComponent::shader.uniform_texture_2d(atlas.texture, 0);
    for (int i = 0; i < HOTBAR_SIZE; i++) {
        float u_x = 1.0f / window->size.x,
              u_y = 1.0f / window->size.y;
        float w = u_x * 80,
              h = u_y * 80;
        float x1 = -w * (HOTBAR_SIZE / 2.0f - i),
              x2 = x1 + w;
        float y1 = -1.0f + 0.1f,
              y2 = y1 + h;

        std::vector<float> vertices = {
            x1, y2,
            x1, y1,
            x2, y1,
            x2, y2,
        };

        unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3,
        };

        if (i == player->hotbar_idx) {
            vertices.push_back(atlas.sprite_uv({2, 0}).x);
            vertices.push_back(atlas.sprite_uv({2, 0}).y);
            vertices.push_back(atlas.sprite_uv({2, 1}).x);
            vertices.push_back(atlas.sprite_uv({2, 1}).y);
            vertices.push_back(atlas.sprite_uv({1, 1}).x);
            vertices.push_back(atlas.sprite_uv({1, 1}).y);
            vertices.push_back(atlas.sprite_uv({1, 0}).x);
            vertices.push_back(atlas.sprite_uv({1, 0}).y);
        } else {
            vertices.push_back(atlas.sprite_uv({1, 0}).x);
            vertices.push_back(atlas.sprite_uv({1, 0}).y);
            vertices.push_back(atlas.sprite_uv({1, 1}).x);
            vertices.push_back(atlas.sprite_uv({1, 1}).y);
            vertices.push_back(atlas.sprite_uv({0, 1}).x);
            vertices.push_back(atlas.sprite_uv({0, 1}).y);
            vertices.push_back(atlas.sprite_uv({0, 0}).x);
            vertices.push_back(atlas.sprite_uv({0, 0}).y);
        }

        UIComponent::ibo.buffer(sizeof(indices), indices);
        UIComponent::vbo.buffer(vertices.size() * sizeof(float), &vertices[0]);

        UIComponent::vao.attr(UIComponent::vbo, 0, 2, GL_FLOAT, 0, 0);
        UIComponent::vao.attr(UIComponent::vbo, 1, 2, GL_FLOAT, 0, (4 * 2) * sizeof(float));

        UIComponent::vao.bind();
        UIComponent::ibo.bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }
}
