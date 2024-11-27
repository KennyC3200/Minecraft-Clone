#include "chunk.hpp"

Chunk::Chunk(glm::ivec3 position)
    : position(position)
{
    data = new Block[ChunkMesh::CHUNK_VOLUME];

    std::fill(data, data + ChunkMesh::CHUNK_VOLUME, BLOCK_DIRT);

    for (int x = 0; x < ChunkMesh::CHUNK_SIZE.x; x++) {
        for (int y = 0; y < ChunkMesh::CHUNK_SIZE.y / 2; y++) {
            for (int z = 0; z < ChunkMesh::CHUNK_SIZE.z; z++) {
                data[ChunkMesh::chunk_pos_to_idx(x, y, z)] = BLOCK_STONE;
            }
        }
    }

    for (int x = 0; x < ChunkMesh::CHUNK_SIZE.x; x++) {
        for (int z = 0; z < ChunkMesh::CHUNK_SIZE.z; z++) {
            data[ChunkMesh::chunk_pos_to_idx(x, ChunkMesh::CHUNK_SIZE.z - 1, z)] = BLOCK_GRASS;
        }
    }

    mesh = new ChunkMesh(data, &this->position);
    meshed = false;
}

Chunk::Chunk(glm::ivec3 position, BlockID fill)
    : position(position)
{
    data = new Block[ChunkMesh::CHUNK_VOLUME];
    std::fill(data, data + ChunkMesh::CHUNK_VOLUME, fill);

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
