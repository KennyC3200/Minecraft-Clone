#pragma once

#include "../util/util.hpp"
#include "chunk.hpp"

class World {
public:
    void init();
    void destroy();
    void render();

    Chunk *chunk_get(glm::ivec3 position);
    int chunks_idx(int x, int y, int z);
    int chunks_idx(glm::ivec3 position);

    BlockData *block_get(glm::ivec3 position);

    Chunk **chunks;

    // number of chunks
    size_t _chunks_size;

    // number of chunks as vector
    glm::ivec3 chunks_size;

    // the ground y-position value
    int y_ground;
};
