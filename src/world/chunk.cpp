#include "chunk.hpp"

Chunk::Chunk(glm::vec<3, int> position):
position(position)
{
    data = new uint64_t[CHUNK_VOLUME];
    std::fill(data, data + CHUNK_VOLUME, BLOCK_DIRT);
    for (int x = 0; x < CHUNK_SIZE_X; x++) {
        for (int z = 0; z < CHUNK_SIZE_Z; z++) {
            data[x * CHUNK_SIZE_X + z * CHUNK_SIZE_Z + CHUNK_SIZE_Y - 1] = BLOCK_GRASS;
        }
    }

    mesh = new ChunkMesh(data, &this->position);
    mesh->prepare();
    mesh->mesh();
}

Chunk::~Chunk() {
    delete mesh;
    delete[] data;
}

void Chunk::init() {
    ChunkMesh::init();
}

void Chunk::render() {
    mesh->render();
}
