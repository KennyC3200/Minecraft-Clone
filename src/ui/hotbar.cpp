#include "hotbar.h"

void Hotbar::Init(Player* player) {
    this->player = player;

    toggled = true;
    atlas = SpriteAtlas("res/images/hotbar.png", "tex", {22, 22});
}

void Hotbar::Render() {
    if (!toggled) {
        return;
    }

    for (int i = 0; i < Player::hotbar_size; i++) {
        glm::vec2 unit = 1.0f / glm::vec2(window->size);
        glm::vec2 size = unit * 80.0f;
        glm::vec2 p1 = {-size.x * (Player::hotbar_size / 2.0f - i), -1.0f + 0.05f};
        glm::vec2 p2 = {p1.x + size.x, p1.y + size.y};

        if (player->hotbar[i] != BLOCK_NONE) {
            RenderItems(p1 + 12.0f * unit, p2 - 12.0f * unit, player->hotbar[i]);
        }
        RenderHotbar(p1, p2, i == player->current_hotbar_idx);
    }
}

void Hotbar::RenderHotbar(glm::vec2 p1, glm::vec2 p2, bool toggled) {
    UIComponent::shader.UniformTexture2D(atlas.texture, 0);

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
        vertices.push_back(atlas.SpriteUV({2, 0}).x);
        vertices.push_back(atlas.SpriteUV({2, 0}).y);
        vertices.push_back(atlas.SpriteUV({2, 1}).x);
        vertices.push_back(atlas.SpriteUV({2, 1}).y);
        vertices.push_back(atlas.SpriteUV({1, 1}).x);
        vertices.push_back(atlas.SpriteUV({1, 1}).y);
        vertices.push_back(atlas.SpriteUV({1, 0}).x);
        vertices.push_back(atlas.SpriteUV({1, 0}).y);
    } else {
        vertices.push_back(atlas.SpriteUV({1, 0}).x);
        vertices.push_back(atlas.SpriteUV({1, 0}).y);
        vertices.push_back(atlas.SpriteUV({1, 1}).x);
        vertices.push_back(atlas.SpriteUV({1, 1}).y);
        vertices.push_back(atlas.SpriteUV({0, 1}).x);
        vertices.push_back(atlas.SpriteUV({0, 1}).y);
        vertices.push_back(atlas.SpriteUV({0, 0}).x);
        vertices.push_back(atlas.SpriteUV({0, 0}).y);
    }

    UIComponent::ibo.Buffer(indices.size() * sizeof(unsigned int), &indices[0]);
    UIComponent::vbo.Buffer(vertices.size() * sizeof(float), &vertices[0]);

    UIComponent::vao.AttribPointer(UIComponent::vbo, 0, 2, GL_FLOAT, 0, 0);
    UIComponent::vao.AttribPointer(UIComponent::vbo, 1, 2, GL_FLOAT, 0, (4 * 2) * sizeof(float));

    UIComponent::vao.Bind();
    UIComponent::ibo.Bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Hotbar::RenderItems(glm::vec2 p1, glm::vec2 p2, BlockID block) {
    UIComponent::shader.UniformTexture2D(BlockMesh::GetAtlas().texture, "tex", 0);

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

    glm::vec2 uv_min = BlockMesh::Get(block).GetFace(NORTH).uv_min;
    glm::vec2 uv_max = BlockMesh::Get(block).GetFace(NORTH).uv_max;

    vertices.push_back(uv_min.x);
    vertices.push_back(1 - uv_min.y);
    vertices.push_back(uv_min.x);
    vertices.push_back(1 - uv_max.y);
    vertices.push_back(uv_max.x);
    vertices.push_back(1 - uv_max.y);
    vertices.push_back(uv_max.x);
    vertices.push_back(1 - uv_min.y);

    UIComponent::ibo.Buffer(indices.size() * sizeof(unsigned int), &indices[0]);
    UIComponent::vbo.Buffer(vertices.size() * sizeof(float), &vertices[0]);

    UIComponent::vao.AttribPointer(UIComponent::vbo, 0, 2, GL_FLOAT, 0, 0);
    UIComponent::vao.AttribPointer(UIComponent::vbo, 1, 2, GL_FLOAT, 0, (4 * 2) * sizeof(float));

    UIComponent::vao.Bind();
    UIComponent::ibo.Bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
