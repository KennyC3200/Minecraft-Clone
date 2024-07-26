#pragma once

#include "../util/util.hpp"
#include "chunk.hpp"

class World {
public:
    void init();
    void destroy();
    void render();

    Chunk **chunks;

    // the number of chunks
    glm::ivec3 chunks_size;
    size_t _chunks_size;

    Chunk *chunk_get(glm::ivec3 position);
    int chunks_idx(int x, int y, int z);
    int chunks_idx(glm::ivec3 position);

    BlockData *block_get(glm::ivec3 position);
};
