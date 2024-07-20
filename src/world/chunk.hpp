#pragma once

#include "chunk_mesh.hpp"
#include "block.hpp"

class Chunk {
public:
    Chunk(glm::vec<3, int> position);
    ~Chunk();

    static void init();

    void neighbors_set(Chunk *chunks[6]);

    void render();

    glm::vec<3, int> position;

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
private:
    ChunkMesh *mesh;
    bool meshed;
};
