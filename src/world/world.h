#pragma once

#include "../util/util.h"
#include "generation/generation.h"
#include "chunk.h"

class World {
public:
    void init();
    void destroy();
    void render();

    Chunk *get_chunk(glm::ivec3 position);
    int get_chunk_idx(glm::ivec3 position);
    Block *get_block(glm::ivec3 chunk_position);

    Chunk **chunks;
    glm::ivec3 chunk_position;

    /* Chunks size as a vector and size_t */
    glm::ivec3 chunks_size;
    size_t chunks_count;

    /* Ground level y-position */
    int ground_level;
private:
    void init_chunks();

    /* World generation */
    Generation generation;
};
