#pragma once

#include "block.h"
#include "chunk_mesh.h"
#include "fast_noise_lite.h"

class Chunk {
public:
    Chunk();
    Chunk(glm::ivec3 position, int ground_level);

    static void Init();

    static int PosToIdx(int x, int y, int z);
    static int PosToIdx(glm::ivec3 pos);

    void Generate(glm::ivec3 position, int ground_level);
    void Render();
    void SetAdjacent(enum Direction direction, Chunk* chunk);

    // Get a block given the blocks position in the chunk
    Block& GetBlock(int x, int y, int z);
    Block& GetBlock(glm::ivec3 pos);

    // Sets the current chunk and adjacent chunks dirty
    void SetDirty();

    static constexpr glm::ivec3 size = {16, 16, 16};
    static constexpr int volume = size.x * size.y * size.z;
    static FastNoiseLite noise;

private:
    glm::ivec3 position;

    // Blocks for the chunk
    Block blocks[volume];

    // Adjacent chunks, used for optimizing between chunks
    Chunk* adjacents[6];

    ChunkMesh mesh;
    bool meshed;
};
