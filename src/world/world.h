#pragma once

#include "chunk.h"
#include "../util/thread_pool.h"

class World {
public:
    void Init(ThreadPool* thread_pool);
    void Destroy();
    void Render();

    // Get the chunk index, given a CHUNK position
    int ChunkIdx(int x, int y, int z);
    int ChunkIdx(glm::ivec3 position);

    // Load new chunks in a direction
    void GenerateChunks(enum Direction direction);

    Chunk* GetChunk(int x, int y, int z);
    Chunk* GetChunk(glm::ivec3 position);
    Block* GetBlock(int x, int y, int z);
    Block* GetBlock(glm::ivec3 position);
    inline glm::ivec3 GetChunksSize() { return chunks_size; }
    inline size_t GetChunksCount() { return chunks_count; }
    inline glm::ivec3 GetPosition() { return position; }

    bool generate = true;

private:
    void InitChunks();
    void InitChunkAdjacents(int x, int y, int z);
    void InitChunksAdjacents();

    void GenerateChunksNorth();
    void GenerateChunksSouth();
    void GenerateChunksEast();
    void GenerateChunksWest();

    ThreadPool* thread_pool;

    Chunk** chunks;

    // Chunks size as a vector and size_t
    glm::ivec3 chunks_size;
    size_t chunks_count;

    // The ground level y-value
    int ground_level;

    // Position where the world is being rendered from
    glm::ivec3 position;
};
