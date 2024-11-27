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
