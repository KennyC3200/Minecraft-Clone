#include "chunk.hpp"

Chunk::Chunk(glm::ivec3 position):
    position(position)
{
    data = new Block[CHUNK_VOLUME];
    std::fill(data, data + CHUNK_VOLUME, BLOCK_DIRT);
    for (int x = 0; x < CHUNK_SIZE_X; x++) {
        for (int y = 0; y < CHUNK_SIZE_Y / 2; y++) {
            for (int z = 0; z < CHUNK_SIZE_Z; z++) {
                data[CHUNK_POS_TO_IDX(x, y, z)] = BLOCK_STONE;
            }
        }
    }
    for (int x = 0; x < CHUNK_SIZE_X; x++) {
        for (int z = 0; z < CHUNK_SIZE_Z; z++) {
            data[CHUNK_POS_TO_IDX(x, CHUNK_SIZE_Y - 1, z)] = BLOCK_GRASS;
        }
    }

    mesh = new ChunkMesh(data, &this->position);
    meshed = false;
}

Chunk::Chunk(glm::ivec3 position, BlockID fill):
    position(position)
{
    data = new Block[CHUNK_VOLUME];
    std::fill(data, data + CHUNK_VOLUME, fill);

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

void Chunk::neighbors_set(Chunk *neighbors[6]) {
    ChunkMesh *mesh_neighbors[6];
    for (int i = 0; i < 6; i++) {
        if (neighbors[i]) {
            this->neighbors[i] = neighbors[i];
            mesh_neighbors[i]  = neighbors[i]->mesh;
        } else {
            this->neighbors[i] = nullptr;
            mesh_neighbors[i]  = nullptr;
        }
    }
    mesh->neighbors_set(mesh_neighbors);
}

void Chunk::render() {
    if (!meshed) {
        mesh->mesh();
        meshed = true;
    }
    mesh->render();
}
