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

    for (int i = 0; i < HOTBAR_SIZE; i++) {
        glm::vec2 unit = 1.0f / glm::vec2(window->size);
        glm::vec2 size = unit * 80.0f;
        glm::vec2 p1 = {-size.x * (HOTBAR_SIZE / 2.0f - i), -1.0f + 0.05f};
        glm::vec2 p2 = {p1.x + size.x, p1.y + size.y};

        if (player->hotbar[i] != BLOCK_NONE) {
            render_items(p1 + 12.0f * unit, p2 - 12.0f * unit, player->hotbar[i]);
        }
        render_hotbar(p1, p2, i == player->hotbar_idx);
    }
}

void Hotbar::render_hotbar(glm::vec2 p1, glm::vec2 p2, bool toggled) {
    UIComponent::shader.uniform_texture_2d(atlas.texture, 0);

    std::vector<float> vertices = {
        p1.x, p2.y,
        p1.x, p1.y,
        p2.x, p1.y,
        p2.x, p2.y,
    };

    std::vector<unsigned int> indices = {
        0, 1, 3,
        1, 2, 3,
    };

    if (toggled) {
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

    UIComponent::ibo.buffer(indices.size() * sizeof(unsigned int), &indices[0]);
    UIComponent::vbo.buffer(vertices.size() * sizeof(float), &vertices[0]);

    UIComponent::vao.attr(UIComponent::vbo, 0, 2, GL_FLOAT, 0, 0);
    UIComponent::vao.attr(UIComponent::vbo, 1, 2, GL_FLOAT, 0, (4 * 2) * sizeof(float));

    UIComponent::vao.bind();
    UIComponent::ibo.bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Hotbar::render_items(glm::vec2 p1, glm::vec2 p2, BlockType block) {
    UIComponent::shader.uniform_texture_2d(Block::atlas.texture, "tex", 0);

    std::vector<float> vertices = {
        p1.x, p2.y,
        p1.x, p1.y,
        p2.x, p1.y,
        p2.x, p2.y,
    };

    std::vector<unsigned int> indices = {
        0, 1, 3,
        1, 2, 3,
    };

    glm::vec2 uv_min = Block::blocks[block].mesh.faces[NORTH].uv_min,
              uv_max = Block::blocks[block].mesh.faces[NORTH].uv_max;
    vertices.push_back(uv_min.x);
    vertices.push_back(1 - uv_min.y);
    vertices.push_back(uv_min.x);
    vertices.push_back(1 - uv_max.y);
    vertices.push_back(uv_max.x);
    vertices.push_back(1 - uv_max.y);
    vertices.push_back(uv_max.x);
    vertices.push_back(1 - uv_min.y);

    UIComponent::ibo.buffer(indices.size() * sizeof(unsigned int), &indices[0]);
    UIComponent::vbo.buffer(vertices.size() * sizeof(float), &vertices[0]);

    UIComponent::vao.attr(UIComponent::vbo, 0, 2, GL_FLOAT, 0, 0);
    UIComponent::vao.attr(UIComponent::vbo, 1, 2, GL_FLOAT, 0, (4 * 2) * sizeof(float));

    UIComponent::vao.bind();
    UIComponent::ibo.bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
