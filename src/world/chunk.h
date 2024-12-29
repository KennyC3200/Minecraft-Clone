#pragma once

#include "generation/generation.h"
#include "chunk_mesh.h"
#include "block.h"

class Chunk {
public:
    Chunk(glm::ivec3 position);
    Chunk(glm::ivec3 position, BlockID fill);
    ~Chunk();

    static void init();

    void set_dirty();

    void neighbors_set(Chunk *neighbors[6]);

    void render();

    glm::ivec3 position;

    // 3d array of block data
    Block *blocks;

    bool meshed;
    Chunk *neighbors[6];
private:
    ChunkMesh *mesh;
};
