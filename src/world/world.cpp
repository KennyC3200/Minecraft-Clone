#include "world.hpp"

void World::init() {
    Block::init();
    Chunk::init();

    chunks_size = {10, 1, 10};
    _chunks_size = chunks_size.x * chunks_size.y * chunks_size.z;
    chunks = new Chunk*[_chunks_size];
    for (int x = 0; x < chunks_size.x; x++) {
        for (int y = 0; y < chunks_size.y; y++) {
            for (int z = 0; z < chunks_size.z; z++) {
                chunks[chunks_idx(x, y, z)] = new Chunk({x, y, z});
            }
        }
    }
    for (int x = 0; x < chunks_size.x; x++) {
        for (int y = 0; y < chunks_size.y; y++) {
            for (int z = 0; z < chunks_size.z; z++) {
                Chunk *neighbors[6];
                neighbors[SOUTH] = z + 1 <  chunks_size.z ? chunks[chunks_idx(x, y, z + 1)] : nullptr;
                neighbors[NORTH] = z - 1 >= 0             ? chunks[chunks_idx(x, y, z - 1)] : nullptr;
                neighbors[EAST]  = x + 1 <  chunks_size.x ? chunks[chunks_idx(x + 1, y, z)] : nullptr;
                neighbors[WEST]  = x - 1 >= 0             ? chunks[chunks_idx(x - 1, y, z)] : nullptr;
                neighbors[UP]    = y + 1 <  chunks_size.y ? chunks[chunks_idx(x, y + 1, z)] : nullptr;
                neighbors[DOWN]  = y - 1 >= 0             ? chunks[chunks_idx(x, y - 1, z)] : nullptr;
                chunks[chunks_idx(x, y, z)]->neighbors_set(neighbors);
            }
        }
    }
}

void World::destroy() {
    for (size_t i = 0; i < _chunks_size; i++) {
        delete chunks[i];
    }
    delete[] chunks;
}

void World::render() {
    ChunkMesh::shader.bind();
    ChunkMesh::shader.uniform_texture_2d(Block::atlas.texture, 0);

    for (size_t i = 0; i < _chunks_size; i++) {
        chunks[i]->render();
    }
}

Chunk *World::chunk_get(glm::ivec3 position) {
    return chunks[chunks_idx(position)];
}

int World::chunks_idx(int x, int y, int z) {
    return x * chunks_size.y * chunks_size.z + z * chunks_size.y + y;
}

int World::chunks_idx(glm::ivec3 position) {
    return position.x * chunks_size.y * chunks_size.z + position.z * chunks_size.y + position.y;
}

BlockData *World::block_get(glm::ivec3 position) {
    if (
        position.x < 0 || position.x >= CHUNK_SIZE_X * chunks_size.x ||
        position.y < 0 || position.y >= CHUNK_SIZE_Y * chunks_size.y ||
        position.z < 0 || position.z >= CHUNK_SIZE_Z * chunks_size.z
    ) {
        return nullptr;
    }

    glm::ivec3 chunk_idx = position / ChunkMesh::chunk_size;
    glm::ivec3 block_idx = position - chunk_idx * ChunkMesh::chunk_size;
    return &chunks[chunks_idx(chunk_idx)]->data[CHUNK_POS_TO_IDX(block_idx.x, block_idx.y, block_idx.z)];
}
