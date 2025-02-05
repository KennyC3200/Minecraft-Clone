#pragma once

#include "block.h"
#include "../gfx/sprite_atlas.h"

#include <cstdint>

typedef struct {
    // UV coordinates of the sprite
    glm::vec2 uv_min, uv_max;
    float uv_coordinates[4 * 2];

    // Sprite coordinates
    glm::ivec2 sprite_coordinates[4];
} Face;

class BlockMesh {
public:
    static void Init();
    static void Destroy();

    Face GetFace(enum Direction direction);
    static SpriteAtlas& GetAtlas();
    static BlockMesh& Get(BlockID block_ID);

    // Add a face to the BlockMesh
    // @param direction Direction of the face to add
    // @param sprite_min The minimum sprite coordinate (top-left coordinate, as sprite coordinates)
    // @param sprite_max The maximum sprite coordinate (bottom-right coordinate, as sprite coordinates)
    void AddFace(enum Direction direction, glm::ivec2 sprite_min, glm::ivec2 sprite_max);

    void MeshFace(
        enum Direction direction,
        glm::ivec3 position,
        std::vector<uint32_t>& vertices,
        std::vector<uint32_t>& indices
    );

private:
    static SpriteAtlas atlas;
    static BlockMesh meshes[BLOCK_LAST];

    static constexpr unsigned int vertices[] = {
        // North (-z)
        0, 0, 0,
        1, 0, 0,
        0, 1, 0,
        1, 1, 0,

        // South (+z)
        0, 0, 1,
        1, 0, 1,
        0, 1, 1,
        1, 1, 1,

        // East (+x)
        1, 0, 1,
        1, 0, 0,
        1, 1, 1,
        1, 1, 0,

        // West (-x)
        0, 0, 1,
        0, 0, 0,
        0, 1, 1,
        0, 1, 0,

        // Up (+y)
        0, 1, 1,
        1, 1, 1,
        0, 1, 0,
        1, 1, 0,

        // Down (-y)
        0, 0, 1,
        1, 0, 1,
        0, 0, 0,
        1, 0, 0,
    };

    static constexpr unsigned int indices[] = {
        2,  0,  1,
        2,  3,  1
    };

    Face faces[6];
};
