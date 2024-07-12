#pragma once

#include "chunk_mesh.hpp"
#include "block.hpp"

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 16
#define CHUNK_SIZE_Z 16
#define CHUNK_VOLUME (CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z)

class Chunk {
public:
    Chunk(glm::vec<2, int> position);
    ~Chunk();

    // chunk data stored in a 3d array
    // each u64 has the following bit fields:
    // - 28 bits metadata/extra
    // - 4 bits sunlight intensity
    // - 4 bits R light
    // - 4 bits G light
    // - 4 bits B light
    // - 4 bits light intensity
    // - 16 bits block id
    uint64_t *data;

    glm::vec<2, int> position;
    ChunkMesh mesh;
};
