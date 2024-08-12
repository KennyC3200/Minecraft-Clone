#pragma once

#include "../util/util.hpp"
#include "chunk.hpp"
#include "generation/generation.hpp"

class World {
public:
    void init();
    void destroy();
    void render();

    Chunk *chunk_get(glm::ivec3 position);
    int chunks_idx(glm::ivec3 position);
    void chunks_generate(glm::ivec3 position);

    BlockData *block_get(glm::ivec3 chunk_position);

    Chunk **chunks;
    glm::ivec3 chunk_position;

    // number of chunks
    size_t _chunks_size;

    // number of chunks as vector
    glm::ivec3 chunks_size;

    // ground level y-position
    int ground_level;
private:
    void init_chunks();
    void init_chunks_neighbors();

    // world generation
    Generation generation;
};
