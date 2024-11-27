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

    static Shader shader;
    static constexpr glm::ivec3 chunk_size = {CHUNK_SIZE_X, CHUNK_SIZE_Y, CHUNK_SIZE_Z};

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
