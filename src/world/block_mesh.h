#pragma once

#include "block.h"
#include "../util/util.h"
#include "../gfx/sprite_atlas.h"

typedef struct {
    glm::vec2 uv_min, uv_max;
    float uv_coordinates[4 * 2];
} Face;

class BlockMesh {
public:
    static void Init();
    static void Destroy();
    static const SpriteAtlas GetAtlas();
    static const BlockMesh Get(BlockID block_ID);

    /*
     * Add a face to the BlockMesh static meshes array
     * @param direction The direction of the block face
     * @param uv_min The min uv coordinate of the face
     * @param uv_max The max uv coordinate of the face
     * */
    void AddFace(enum Direction direction, glm::vec2 uv_min, glm::vec2 uv_max);

    /* 
     * Mesh a face in the chunk 
     * @param direction The direction of the face to mesh
     * @param position The block's position
     * @param vertices The vertices of the block
     * @param indices The indices of the block
     * */
    void MeshFace(
        enum Direction direction, 
        glm::vec3 position, 
        std::vector<float>& vertices, 
        std::vector<unsigned int>& indices) const;

    Face GetFace(enum Direction direction) const;

private:
    static SpriteAtlas atlas;
    static BlockMesh meshes[BLOCK_LAST];
    
    static constexpr float vertices[] = {
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
