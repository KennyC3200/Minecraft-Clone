#include "world.h"
#include "block_mesh.h"

void World::Init() {
    Chunk::Init();
    BlockMesh::Init();

    chunks_size = {10, 10, 10};
    chunks_count = chunks_size.x * chunks_size.y * chunks_size.z;
    ground_level_y = chunks_size.y * Chunk::size.y / 2;

    InitChunks();
}

void World::Destroy() {
    for (size_t i = 0; i < chunks_count; i++) {
        delete chunks[i];
    }
    delete[] chunks;

    BlockMesh::Destroy();
}

void World::Render() {
    for (size_t i = 0; i < chunks_count; i++) {
        chunks[i]->Render();
    }
}

Chunk* World::GetChunk(glm::ivec3 position) {
    return chunks[GetChunkIdx(position / Chunk::size)];
}

int World::GetChunkIdx(int x, int y, int z) {
    return (x * chunks_size.y * chunks_size.z) + (z * chunks_size.y) + (y);
}

int World::GetChunkIdx(glm::ivec3 position) {
    return
        (position.x * chunks_size.y * chunks_size.z) +
        (position.z * chunks_size.y) +
        (position.y);
}

Block* World::GetBlock(glm::ivec3 position) {
    if (
        position.x < 0 || position.x >= Chunk::size.x * chunks_size.x ||
        position.y < 0 || position.y >= Chunk::size.y * chunks_size.y ||
        position.z < 0 || position.z >= Chunk::size.z * chunks_size.z
    ) {
        return nullptr;
    }

    glm::ivec3 chunk_idx = position / Chunk::size;
    glm::ivec3 block_idx = position - chunk_idx * Chunk::size;
    return &chunks[GetChunkIdx(chunk_idx)]->GetBlock(block_idx);
}

void World::InitChunks() {
    chunks = new Chunk*[chunks_count];

    // Init the chunks
    for (int x = 0; x < chunks_size.x; x++) {
        for (int y = 0; y < chunks_size.y; y++) {
            for (int z = 0; z < chunks_size.z; z++) {
                chunks[GetChunkIdx(x, y, z)] = new Chunk(
                    {x * Chunk::size.x, y * Chunk::size.y, z * Chunk::size.z},
                    ground_level_y
                );
            }
        }
    }


    // Init the adjacent chunks
    for (int x = 0; x < chunks_size.x; x++) {
        for (int y = 0; y < chunks_size.y; y++) {
            for (int z = 0; z < chunks_size.z; z++) {
                Chunk* chunk = chunks[GetChunkIdx(x, y, z)];
                chunk->SetAdjacent(NORTH, z - 1 >= 0             ? chunks[GetChunkIdx(x, y, z - 1)] : nullptr);
                chunk->SetAdjacent(SOUTH, z + 1 <  chunks_size.z ? chunks[GetChunkIdx(x, y, z + 1)] : nullptr);
                chunk->SetAdjacent(EAST,  x + 1 <  chunks_size.x ? chunks[GetChunkIdx(x + 1, y, z)] : nullptr);
                chunk->SetAdjacent(WEST,  x - 1 >= 0             ? chunks[GetChunkIdx(x - 1, y, z)] : nullptr);
                chunk->SetAdjacent(UP,    y + 1 <  chunks_size.y ? chunks[GetChunkIdx(x, y + 1, z)] : nullptr);
                chunk->SetAdjacent(DOWN,  y - 1 >= 0             ? chunks[GetChunkIdx(x, y - 1, z)] : nullptr);
            }
        }
    }
}

glm::ivec3 World::GetChunksSize() {
    return chunks_size;
}

size_t World::GetChunksCount() {
    return chunks_count;
}
