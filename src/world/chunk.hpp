#pragma once

#include "chunk_mesh.hpp"
#include "block.hpp"
#include "generation/generation.hpp"

class Chunk {
public:
    Chunk(glm::ivec3 position);
    Chunk(glm::ivec3 position, BlockID fill);
    ~Chunk();

    static void init();

    void neighbors_set(Chunk *neighbors[6]);

    void render();

    glm::ivec3 position;

    // 3d array of block data
    BlockData *data;

    bool meshed;
    Chunk *neighbors[6];
private:
    ChunkMesh *mesh;
};
