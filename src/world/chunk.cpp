#include "chunk.hpp"

Chunk::Chunk(glm::ivec3 position)
    : position(position)
{
    data = new Block[ChunkMesh::chunk_volume];

    std::fill(data, data + ChunkMesh::chunk_volume, BLOCK_DIRT);

    for (int x = 0; x < ChunkMesh::chunk_size.x; x++) {
        for (int y = 0; y < ChunkMesh::chunk_size.y / 2; y++) {
            for (int z = 0; z < ChunkMesh::chunk_size.z; z++) {
                data[ChunkMesh::chunk_pos_to_idx(x, y, z)] = BLOCK_STONE;
            }
        }
    }

    for (int x = 0; x < ChunkMesh::chunk_size.x; x++) {
        for (int z = 0; z < ChunkMesh::chunk_size.z; z++) {
            data[ChunkMesh::chunk_pos_to_idx(x, ChunkMesh::chunk_size.z - 1, z)] = BLOCK_GRASS;
        }
    }

    mesh = new ChunkMesh(data, &this->position);
    meshed = false;
}

Chunk::Chunk(glm::ivec3 position, BlockID fill)
    : position(position)
{
    data = new Block[ChunkMesh::chunk_volume];
    std::fill(data, data + ChunkMesh::chunk_volume, fill);

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
