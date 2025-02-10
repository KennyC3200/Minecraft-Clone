#include "world.h"
#include "block_mesh.h"

void World::Init() {
    Chunk::Init();
    BlockMesh::Init();

    chunks_size = {24, 10, 24};
    chunks_count = chunks_size.x * chunks_size.y * chunks_size.z;
    ground_level = chunks_size.y * Chunk::size.y / 2;
    position = {0, 0, 0};

    InitChunks();
    InitChunksAdjacents();
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

int World::ChunkIdx(int x, int y, int z) {
    return (x * chunks_size.y * chunks_size.z) + (y * chunks_size.z) + (z);
}

int World::ChunkIdx(glm::ivec3 position) {
    return ChunkIdx(position.x, position.y, position.z);
}

void World::GenerateChunks(enum Direction direction) {
    if (!generate) {
        return;
    }

    switch (direction) {
        case EAST: {
            Chunk* tmp[chunks_size.y * chunks_size.z];
            for (int y = 0; y < chunks_size.y; y++) {
                for (int z = 0; z < chunks_size.z; z++) {
                    tmp[y * chunks_size.z + z] = chunks[ChunkIdx(0, y, z)];
                }
            }
            for (int x = 0; x < chunks_size.x - 1; x++) {
                for (int y = 0; y < chunks_size.y; y++) {
                    for (int z = 0; z < chunks_size.z; z++) {
                        chunks[ChunkIdx(x, y, z)] = chunks[ChunkIdx(x + 1, y, z)];
                    }
                }
            }
            for (int y = 0; y < chunks_size.y; y++) {
                for (int z = 0; z < chunks_size.z; z++) {
                    chunks[ChunkIdx(chunks_size.x - 1, y, z)] = tmp[y * chunks_size.z + z];
                }
            }
            for (int y = 0; y < chunks_size.y; y++) {
                for (int z = 0; z < chunks_size.z; z++) {
                    // Generate new chunk
                    tmp[y * chunks_size.z + z]->Generate(
                        {
                            position.x + chunks_size.x * Chunk::size.x,
                            position.y + y * Chunk::size.y,
                            position.z + z * Chunk::size.z
                        },
                        ground_level);
                    tmp[y * chunks_size.z + z]->SetDirty();
                    InitChunkAdjacents(chunks_size.x - 1, y, z);

                    // Set adjacent chunk dirty
                    chunks[ChunkIdx(chunks_size.x - 2, y, z)]->SetDirty();
                    InitChunkAdjacents(chunks_size.x - 2, y, z);
                }
            }

            position.x += Chunk::size.x;
            break;
        }
        case WEST: {
            Chunk* tmp[chunks_size.y * chunks_size.z];
            for (int y = 0; y < chunks_size.y; y++) {
                for (int z = 0; z < chunks_size.z; z++) {
                    tmp[y * chunks_size.z + z] = chunks[ChunkIdx(chunks_size.x - 1, y, z)];
                }
            }
            for (int x = chunks_size.x - 1; x > 0; x--) {
                for (int y = 0; y < chunks_size.y; y++) {
                    for (int z = 0; z < chunks_size.z; z++) {
                        chunks[ChunkIdx(x, y, z)] = chunks[ChunkIdx(x - 1, y, z)];
                    }
                }
            }
            for (int y = 0; y < chunks_size.y; y++) {
                for (int z = 0; z < chunks_size.z; z++) {
                    chunks[ChunkIdx(0, y, z)] = tmp[y * chunks_size.z + z];
                }
            }
            for (int y = 0; y < chunks_size.y; y++) {
                for (int z = 0; z < chunks_size.z; z++) {
                    // Generate new chunk
                    tmp[y * chunks_size.z + z]->Generate(
                        {
                            position.x - Chunk::size.x,
                            position.y + y * Chunk::size.y,
                            position.z + z * Chunk::size.z
                        },
                        ground_level);
                    tmp[y * chunks_size.z + z]->SetDirty();
                    InitChunkAdjacents(0, y, z);

                    // Set adjacent chunk dirty
                    chunks[ChunkIdx(1, y, z)]->SetDirty();
                    InitChunkAdjacents(1, y, z);
                }
            }

            position.x -= Chunk::size.x;
            break;
        }
        case NORTH: {
            Chunk* tmp[chunks_size.x * chunks_size.y];
            for (int x = 0; x < chunks_size.x; x++) {
                for (int y = 0; y < chunks_size.y; y++) {
                    tmp[x * chunks_size.y + y] = chunks[ChunkIdx(x, y, chunks_size.z - 1)];
                }
            }
            for (int x = 0; x < chunks_size.x; x++) {
                for (int y = 0; y < chunks_size.y; y++) {
                    for (int z = chunks_size.z - 1; z > 0; z--) {
                        chunks[ChunkIdx(x, y, z)] = chunks[ChunkIdx(x, y, z - 1)];
                    }
                }
            }
            for (int x = 0; x < chunks_size.x; x++) {
                for (int y = 0; y < chunks_size.y; y++) {
                    chunks[ChunkIdx(x, y, 0)] = tmp[x * chunks_size.y + y];
                }
            }
            for (int x = 0; x < chunks_size.x; x++) {
                for (int y = 0; y < chunks_size.y; y++) {
                    // Generate new chunk
                    tmp[x * chunks_size.y + y]->Generate(
                        {
                            position.x + x * Chunk::size.x,
                            position.y + y * Chunk::size.y,
                            position.z - Chunk::size.z
                        },
                    ground_level);
                    tmp[x * chunks_size.y + y]->SetDirty();
                    InitChunkAdjacents(x, y, 0);

                    // Set adjacent chunk dirty
                    chunks[ChunkIdx(x, y, 1)]->SetDirty();
                    InitChunkAdjacents(x, y, 1);
                }
            }
            position.z -= Chunk::size.z;
            break;
        }
        case SOUTH: {
            Chunk* tmp[chunks_size.x * chunks_size.y];
            for (int x = 0; x < chunks_size.x; x++) {
                for (int y = 0; y < chunks_size.y; y++) {
                    tmp[x * chunks_size.y + y] = chunks[ChunkIdx(x, y, 0)];
                }
            }
            for (int x = 0; x < chunks_size.x; x++) {
                for (int y = 0; y < chunks_size.y; y++) {
                    for (int z = 0; z < chunks_size.z - 1; z++) {
                        chunks[ChunkIdx(x, y, z)] = chunks[ChunkIdx(x, y, z + 1)];
                    }
                }
            }
            for (int x = 0; x < chunks_size.x; x++) {
                for (int y = 0; y < chunks_size.y; y++) {
                    chunks[ChunkIdx(x, y, chunks_size.z - 1)] = tmp[x * chunks_size.y + y];
                }
            }
            for (int x = 0; x < chunks_size.x; x++) {
                for (int y = 0; y < chunks_size.y; y++) {
                    // Generate new chunk
                    tmp[x * chunks_size.y + y]->Generate(
                        {
                            position.x + x * Chunk::size.x,
                            position.y + y * Chunk::size.y,
                            position.z + chunks_size.z * Chunk::size.z
                        },
                        ground_level);
                    tmp[x * chunks_size.y + y]->SetDirty();
                    InitChunkAdjacents(x, y, chunks_size.z - 1);

                    // Set adjacent chunk dirty
                    chunks[ChunkIdx(x, y, chunks_size.z - 2)]->SetDirty();
                    InitChunkAdjacents(x, y, chunks_size.z - 2);
                }
            }

            position.z += Chunk::size.z;
            break;
        }
        case UP:
            break;
        case DOWN:
            break;
        default:
            break;
    }
}

Chunk* World::GetChunk(int x, int y, int z) {
    // Block positions relative to the world render position
    int block_x = x - position.x;
    int block_y = y - position.y;
    int block_z = z - position.z;

    // Check bounds
    if (
        block_x < 0 || block_x >= Chunk::size.x * chunks_size.x ||
        block_y < 0 || block_y >= Chunk::size.y * chunks_size.y ||
        block_z < 0 || block_z >= Chunk::size.z * chunks_size.z
    ) {
        return nullptr;
    }

    return chunks[ChunkIdx(
        block_x / Chunk::size.x,
        block_y / Chunk::size.y,
        block_z / Chunk::size.z
    )];
}

Chunk* World::GetChunk(glm::ivec3 position) {
    return GetChunk(position.x, position.y, position.z);
}

Block* World::GetBlock(int x, int y, int z) {
    // Block positions relative to the world render position
    int block_x = x - position.x;
    int block_y = y - position.y;
    int block_z = z - position.z;

    // Get the chunk the block is in
    Chunk* chunk = GetChunk(x, y, z);

    // Need to round negative numbers down
    return chunk ? &chunk->GetBlock(
        block_x - (block_x / Chunk::size.x) * Chunk::size.x,
        block_y - (block_y / Chunk::size.y) * Chunk::size.y,
        block_z - (block_z / Chunk::size.z) * Chunk::size.z)
    : nullptr;
}

Block* World::GetBlock(glm::ivec3 position) {
    return GetBlock(position.x, position.y, position.z);
}

void World::InitChunks() {
    chunks = new Chunk*[chunks_count];
    for (int x = 0; x < chunks_size.x; x++) {
        for (int y = 0; y < chunks_size.y; y++) {
            for (int z = 0; z < chunks_size.z; z++) {
                chunks[ChunkIdx(x, y, z)] = new Chunk(
                    {x * Chunk::size.x, y * Chunk::size.y, z * Chunk::size.z},
                    ground_level
                );
            }
        }
    }
}

void World::InitChunkAdjacents(int x, int y, int z) {
    Chunk* chunk = chunks[ChunkIdx(x, y, z)];
    chunk->SetAdjacent(
        NORTH, z - 1 >= 0 ?
        chunks[ChunkIdx(x, y, z - 1)] : nullptr);
    chunk->SetAdjacent(
        SOUTH, z + 1 <  chunks_size.z ?
        chunks[ChunkIdx(x, y, z + 1)] : nullptr);
    chunk->SetAdjacent(
        EAST, x + 1 < chunks_size.x ?
        chunks[ChunkIdx(x + 1, y, z)] : nullptr);
    chunk->SetAdjacent(
        WEST, x - 1 >= 0 ?
        chunks[ChunkIdx(x - 1, y, z)] : nullptr);
    chunk->SetAdjacent(
        UP, y + 1 <  chunks_size.y ?
        chunks[ChunkIdx(x, y + 1, z)] : nullptr);
    chunk->SetAdjacent(
        DOWN, y - 1 >= 0 ?
        chunks[ChunkIdx(x, y - 1, z)] : nullptr);
}

void World::InitChunksAdjacents() {
    for (int x = 0; x < chunks_size.x; x++) {
        for (int y = 0; y < chunks_size.y; y++) {
            for (int z = 0; z < chunks_size.z; z++) {
                InitChunkAdjacents(x, y, z);
            }
        }
    }
}
