#include "world.hpp"

void World::init() {
    BlockData::init();
    Chunk::init();

    chunks_size = {16, 3, 16};
    ground_level = 2;
    chunk_position = {chunks_size.x / 2, ground_level, chunks_size.z / 2};

    init_chunks();
    init_chunks_neighbors();
}

void World::destroy() {
    for (size_t i = 0; i < _chunks_size; i++) {
        delete chunks[i];
    }
    delete[] chunks;
}

void World::render() {
    ChunkMesh::shader.bind();
    ChunkMesh::shader.uniform_texture_2d(BlockData::atlas.texture, 0);

    for (size_t i = 0; i < _chunks_size; i++) {
        chunks[i]->render();
    }
}

Chunk *World::chunk_get(glm::ivec3 position) {
    return chunks[chunks_idx(position / ChunkMesh::CHUNK_SIZE)];
}

int World::chunks_idx(glm::ivec3 position) {
    return position.x * chunks_size.y * chunks_size.z + position.z * chunks_size.y + position.y;
}

void World::chunks_generate(glm::ivec3 chunk_position) {
    glm::ivec3 diff = chunk_position - chunk_position;

    if (SIGN(diff.x) > 0) {
    }
    if (SIGN(diff.x) < 0) {
    }
    if (SIGN(diff.z) > 0) {
    }
    if (SIGN(diff.z) < 0) {
    }
}

Block *World::block_get(glm::ivec3 position) {
    if (
        position.x < 0 || position.x >= ChunkMesh::CHUNK_SIZE.x * chunks_size.x ||
        position.y < 0 || position.y >= ChunkMesh::CHUNK_SIZE.y * chunks_size.y ||
        position.z < 0 || position.z >= ChunkMesh::CHUNK_SIZE.z * chunks_size.z
    ) {
        return nullptr;
    }

    glm::ivec3 chunk_idx = position / ChunkMesh::CHUNK_SIZE;
    glm::ivec3 block_idx = position - chunk_idx * ChunkMesh::CHUNK_SIZE;
    return &chunks[chunks_idx(chunk_idx)]->data[ChunkMesh::chunk_pos_to_idx(block_idx.x, block_idx.y, block_idx.z)];
}

void World::init_chunks() {
    _chunks_size = chunks_size.x * chunks_size.y * chunks_size.z;
    chunks = new Chunk*[_chunks_size];

    for (int x = 0; x < chunks_size.x; x++) {
        for (int y = 0; y < ground_level; y++) {
            for (int z = 0; z < chunks_size.z; z++) {
                chunks[chunks_idx({x, y, z})] = new Chunk({x, y, z});
            }
        }
        for (int y = ground_level; y < chunks_size.y; y++) {
            for (int z = 0; z < chunks_size.z; z++) {
                chunks[chunks_idx({x, y, z})] = new Chunk({x, y, z}, BLOCK_AIR);
            }
        }
    }
}

void World::init_chunks_neighbors() {
    for (int x = 0; x < chunks_size.x; x++) {
        for (int y = 0; y < chunks_size.y; y++) {
            for (int z = 0; z < chunks_size.z; z++) {
                Chunk *neighbors[6];
                neighbors[SOUTH] = z + 1 <  chunks_size.z ? chunks[chunks_idx({x, y, z + 1})] : nullptr;
                neighbors[NORTH] = z - 1 >= 0             ? chunks[chunks_idx({x, y, z - 1})] : nullptr;
                neighbors[EAST]  = x + 1 <  chunks_size.x ? chunks[chunks_idx({x + 1, y, z})] : nullptr;
                neighbors[WEST]  = x - 1 >= 0             ? chunks[chunks_idx({x - 1, y, z})] : nullptr;
                neighbors[UP]    = y + 1 <  chunks_size.y ? chunks[chunks_idx({x, y + 1, z})] : nullptr;
                neighbors[DOWN]  = y - 1 >= 0             ? chunks[chunks_idx({x, y - 1, z})] : nullptr;
                chunks[chunks_idx({x, y, z})]->neighbors_set(neighbors);
            }
        }
    }
}
