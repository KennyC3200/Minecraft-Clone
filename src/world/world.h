#pragma once

#include "../util/util.h"
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

    glm::ivec3 GetChunksSize();
    size_t GetChunksCount();

private:
    void InitChunks();

    Chunk** chunks;

    // Chunks size as a vector and size_t
    glm::ivec3 chunks_size;
    size_t chunks_count;
};
