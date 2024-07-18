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
    meshed = false;
}

Chunk::~Chunk() {
    delete mesh;
    delete[] data;
}

void Chunk::init() {
    ChunkMesh::init();
}

void Chunk::neighbors_set(Chunk *chunks[6]) {
    ChunkMesh *neighbors[6];
    neighbors[NORTH] = chunks[NORTH] ? chunks[NORTH]->mesh : nullptr;
    neighbors[SOUTH] = chunks[SOUTH] ? chunks[SOUTH]->mesh : nullptr;
    neighbors[EAST]  = chunks[EAST]  ? chunks[EAST]->mesh  : nullptr;
    neighbors[WEST]  = chunks[WEST]  ? chunks[WEST]->mesh  : nullptr;
    neighbors[UP]    = chunks[UP]    ? chunks[UP]->mesh    : nullptr;
    neighbors[DOWN]  = chunks[DOWN]  ? chunks[DOWN]->mesh  : nullptr;
    mesh->neighbors_set(neighbors);
}

void Chunk::render() {
    if (!meshed) {
        mesh->prepare();
        mesh->mesh();
        meshed = true;
    }
    mesh->render();
}
