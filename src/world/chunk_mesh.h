#pragma once

#include "../util/util.h"
#include "../gfx/shader.h"
#include "../gfx/vao.h"
#include "../gfx/vbo.h"
#include "block.h"

class ChunkMesh {
public:
    ChunkMesh(Block *blocks, glm::ivec3 *position);
    ~ChunkMesh();

    static void init();
    static int chunk_pos_to_idx(glm::ivec3 pos);
    static int chunk_pos_to_idx(int x, int y, int z);

    static constexpr glm::ivec3 CHUNK_SIZE = {16, 16, 16};
    static constexpr int CHUNK_VOLUME = CHUNK_SIZE.x * CHUNK_SIZE.y * CHUNK_SIZE.z;

    static Shader shader;

    void neighbors_set(ChunkMesh *neighbors[6]);

    void mesh();
    void render();
private:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    Block *blocks;
    glm::ivec3 *position;
    ChunkMesh *neighbors[6];

    VAO vao;
    VBO vbo, ibo;
};
