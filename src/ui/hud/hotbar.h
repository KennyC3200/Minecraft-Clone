#pragma once

#include "hud_component.h"
#include "../../player/player.h"
#include "../../gfx/sprite_atlas.h"
#include "../../world/block_mesh.h"

class Hotbar : public HudComponent {
public:
    void Init(Player* player);

    void Mesh() override {
        for (int mesh = 0; mesh < MESH_LAST; mesh++) {
            vertices[mesh].clear();
            indices[mesh].clear();
        }

        for (int i = 0; i < Player::hotbar_size; i++) {
            glm::vec2 unit = window->GetPixelUnit();

            // 80 x 80 window pixel units
            glm::vec2 size = 80.0f * unit;

            // The hotbar frame/item is defined by two points, since it is a square
            glm::vec2 p1 = glm::vec2{-size.x * (Player::hotbar_size / 2.0f - i), -1.0f + 0.05f};
            glm::vec2 p2 = glm::vec2{p1.x + size.x, p1.y + size.y};

            if (player->GetHotbarItem(i) != BLOCK_NONE) {
                MeshItem(
                    {p1.x + 12.0f * unit.x, p1.y + 12.0f * unit.y},
                    {p2.x - 12.0f * unit.x, p2.y - 12.0f * unit.y},
                    player->GetHotbarItem(i)
                );
            }
            MeshFrame(p1, p2, i == player->GetCurrentHotbarIdx());
        }
    }

    void Render() override {
        if (!toggled) {
            return;
        }

        for (int mesh = 0; mesh < MESH_LAST; mesh++) {
            if (indices[mesh].size() == 0) {
                continue;
            }

            if (mesh == ITEM_MESH) {
                shader.UniformTexture2D(BlockMesh::GetAtlas(), 0);
            } else if (mesh == FRAME_MESH) {
                shader.UniformTexture2D(atlas, 0);
            }

            ibo.Buffer(indices[mesh].size() * sizeof(unsigned int), &indices[mesh][0]);
            vbo.Buffer(vertices[mesh].size() * sizeof(float), &vertices[mesh][0]);

            vao.AttribPointer(vbo, 0, 2, GL_FLOAT, 4 * sizeof(float), 0 * sizeof(float));
            vao.AttribPointer(vbo, 1, 2, GL_FLOAT, 4 * sizeof(float), 2 * sizeof(float));

            vao.Bind();
            ibo.Bind();

            glDrawElements(GL_TRIANGLES, indices[mesh].size(), GL_UNSIGNED_INT, 0);
        }
    }

private:
    void MeshFrame(glm::vec2 p1, glm::vec2 p2, bool active);
    void MeshItem(glm::vec2 p1, glm::vec2 p2, BlockID block_id);

    Player* player;
    SpriteAtlas atlas;

    enum HotbarMesh {
        ITEM_MESH = 0,
        FRAME_MESH,
        MESH_LAST
    };

    std::vector<float> vertices[MESH_LAST];
    std::vector<unsigned int> indices[MESH_LAST];
};
