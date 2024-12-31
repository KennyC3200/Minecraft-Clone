#pragma once

#include "../util/util.h"
#include "generation/generation.h"
#include "chunk.h"

class World {
public:
    void Init();
    void Destroy();
    void Render();

    Chunk* GetChunk(glm::ivec3 position);

    // Get the chunk index, given a chunk position
    int GetChunkIdx(int x, int y, int z);
    int GetChunkIdx(glm::ivec3 position);

    Block* GetBlock(glm::ivec3 chunk_position);

    Chunk** chunks;
    glm::ivec3 chunk_position;

    // Chunks size as a vector and size_t
    glm::ivec3 chunks_size;
    size_t chunks_count;

    // Ground level y-position
    int ground_level;
private:
    void InitChunks();

    // World generation
    Generation generation;
};
