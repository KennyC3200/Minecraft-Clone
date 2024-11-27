#pragma once

#include "block.hpp"
#include "../util/util.hpp"
#include "../gfx/shader.hpp"
#include "../gfx/vao.hpp"
#include "../gfx/vbo.hpp"

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 16
#define CHUNK_SIZE_Z 16
#define CHUNK_VOLUME (CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z)

#define CHUNK_POS_TO_IDX(x, y, z) ((x) * CHUNK_SIZE_Z * CHUNK_SIZE_Y + (z) * CHUNK_SIZE_Y + (y))

class ChunkMesh {

public:
    ChunkMesh(Block *blocks, glm::ivec3 *position);
    ~ChunkMesh();

    static void init();
    static int chunk_pos_to_idx(int x, int y, int z);

    static Shader shader;
    static constexpr glm::ivec3 chunk_size = {16, 16, 16};
    static constexpr int chunk_volume = chunk_size.x * chunk_size.y * chunk_size.z;

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
