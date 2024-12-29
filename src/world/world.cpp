#include "world.h"

/* Init the world */
void World::init() {
    BlockData::init();
    Chunk::init();

    chunks_size = {16, 3, 16};
    ground_level = 2;
    chunk_position = {chunks_size.x / 2, ground_level, chunks_size.z / 2};

    init_chunks();
}

/* Destroy the world */
void World::destroy() {
    for (size_t i = 0; i < chunks_count; i++) {
        delete chunks[i];
    }
    delete[] chunks;
}

/* Render the world */
void World::render() {
    for (size_t i = 0; i < chunks_count; i++) {
        chunks[i]->render();
    }
}

/* Get the chunk given a CHUNK postiion */
Chunk *World::get_chunk(glm::ivec3 position) {
    return chunks[get_chunk_idx(position / ChunkMesh::CHUNK_SIZE)];
}

/* Get the chunk index given a CHUNK position */
int World::get_chunk_idx(glm::ivec3 position) {
    return (position.x * chunks_size.y * chunks_size.z) + (position.z * chunks_size.y) + (position.y);
}

/* Get the block given a PLAYER position */
Block *World::get_block(glm::ivec3 position) {
    glm::ivec3 CHUNK_SIZE = ChunkMesh::CHUNK_SIZE;

    if (
        position.x < 0 || position.x >= CHUNK_SIZE.x * chunks_size.x ||
        position.y < 0 || position.y >= CHUNK_SIZE.y * chunks_size.y ||
        position.z < 0 || position.z >= CHUNK_SIZE.z * chunks_size.z
    ) {
        return nullptr;
    }

    glm::ivec3 chunk_idx = position / CHUNK_SIZE;
    glm::ivec3 block_idx = position - chunk_idx * CHUNK_SIZE;
    return &chunks[get_chunk_idx(chunk_idx)]->blocks[ChunkMesh::chunk_pos_to_idx(block_idx.x, block_idx.y, block_idx.z)];
}

/* Init the chunks for the world */
void World::init_chunks() {
    chunks_count = chunks_size.x * chunks_size.y * chunks_size.z;
    chunks = new Chunk*[chunks_count];

    /* Init the chunks */
    for (int x = 0; x < chunks_size.x; x++) {
        for (int y = 0; y < ground_level; y++) {
            for (int z = 0; z < chunks_size.z; z++) {
                chunks[get_chunk_idx({x, y, z})] = new Chunk({x, y, z});
            }
        }
        for (int y = ground_level; y < chunks_size.y; y++) {
            for (int z = 0; z < chunks_size.z; z++) {
                chunks[get_chunk_idx({x, y, z})] = new Chunk({x, y, z}, BLOCK_AIR);
            }
        }
    }

    /* Init the adjacent chunks */
    for (int x = 0; x < chunks_size.x; x++) {
        for (int y = 0; y < chunks_size.y; y++) {
            for (int z = 0; z < chunks_size.z; z++) {
                Chunk *neighbors[6];
                neighbors[SOUTH] = z + 1 <  chunks_size.z ? chunks[get_chunk_idx({x, y, z + 1})] : nullptr;
                neighbors[NORTH] = z - 1 >= 0             ? chunks[get_chunk_idx({x, y, z - 1})] : nullptr;
                neighbors[EAST]  = x + 1 <  chunks_size.x ? chunks[get_chunk_idx({x + 1, y, z})] : nullptr;
                neighbors[WEST]  = x - 1 >= 0             ? chunks[get_chunk_idx({x - 1, y, z})] : nullptr;
                neighbors[UP]    = y + 1 <  chunks_size.y ? chunks[get_chunk_idx({x, y + 1, z})] : nullptr;
                neighbors[DOWN]  = y - 1 >= 0             ? chunks[get_chunk_idx({x, y - 1, z})] : nullptr;
                chunks[get_chunk_idx({x, y, z})]->neighbors_set(neighbors);
            }
        }
    }
}
