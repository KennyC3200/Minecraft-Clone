#include "chunk.h"

Chunk::Chunk(glm::ivec3 position)
    : position(position)
{
    blocks = new Block[ChunkMesh::CHUNK_VOLUME];

    std::fill(blocks, blocks + ChunkMesh::CHUNK_VOLUME, BLOCK_DIRT);

    for (int x = 0; x < ChunkMesh::CHUNK_SIZE.x; x++) {
        for (int y = 0; y < ChunkMesh::CHUNK_SIZE.y / 2; y++) {
            for (int z = 0; z < ChunkMesh::CHUNK_SIZE.z; z++) {
                blocks[ChunkMesh::chunk_pos_to_idx(x, y, z)] = BLOCK_STONE;
            }
        }
    }

    for (int x = 0; x < ChunkMesh::CHUNK_SIZE.x; x++) {
        for (int z = 0; z < ChunkMesh::CHUNK_SIZE.z; z++) {
            blocks[ChunkMesh::chunk_pos_to_idx(x, ChunkMesh::CHUNK_SIZE.z - 1, z)] = BLOCK_GRASS;
        }
    }

    mesh = new ChunkMesh(blocks, &this->position);
    meshed = false;
}

Chunk::Chunk(glm::ivec3 position, BlockID fill)
    : position(position)
{
    blocks = new Block[ChunkMesh::CHUNK_VOLUME];
    std::fill(blocks, blocks + ChunkMesh::CHUNK_VOLUME, fill);

    mesh = new ChunkMesh(blocks, &this->position);
    meshed = false;
}

Chunk::~Chunk() {
    delete mesh;
    delete[] blocks;
}

void Chunk::init() {
    ChunkMesh::init();
}

void Chunk::set_dirty() {
    meshed = false;
    for (int i = 0; i < 6; i++) {
        if (neighbors[i] != nullptr) {
            neighbors[i]->meshed = false;
        }
    }
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
