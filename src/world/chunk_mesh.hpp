#pragma once

#include "block.hpp"
#include "../util/util.hpp"
#include "../gfx/shader.hpp"
#include "../gfx/vao.hpp"
#include "../gfx/vbo.hpp"

class ChunkMesh {
public:
    ChunkMesh(Block *blocks, glm::ivec3 *position);
    ~ChunkMesh();

    static void init();
    static int chunk_pos_to_idx(glm::ivec3 pos);
    static int chunk_pos_to_idx(int x, int y, int z);

    static Shader shader;
    static constexpr glm::ivec3 CHUNK_SIZE = {16, 16, 16};
    static constexpr int CHUNK_VOLUME = CHUNK_SIZE.x * CHUNK_SIZE.y * CHUNK_SIZE.z;

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
