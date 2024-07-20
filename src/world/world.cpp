#include "world.hpp"

void World::init(Player *player) {
    this->player = player;

    Block::init();
    Chunk::init();

    chunks_size = {10, 1, 10};
    chunks = new Chunk*[chunks_size_magnitude()];
    for (size_t x = 0; x < chunks_size.x; x++) {
        for (size_t y = 0; y < chunks_size.y; y++) {
            for (size_t z = 0; z < chunks_size.z; z++) {
                chunks[chunks_idx(x, y, z)] = new Chunk({
                    x - chunks_size.x / 2,
                    y - 2,
                    z - chunks_size.z / 2
                });
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
    for (size_t i = 0; i < chunks_size_magnitude(); i++) {
        delete chunks[i];
    }
    delete[] chunks;
}

void World::render() {
    ChunkMesh::shader.bind();
    ChunkMesh::shader.uniform_texture_2d(Block::atlas.texture, 0);

    for (size_t i = 0; i < chunks_size_magnitude(); i++) {
        chunks[i]->render();
    }
}

size_t World::chunks_size_magnitude() {
    return chunks_size.x * chunks_size.y * chunks_size.z;
}

size_t World::chunks_idx(size_t x, size_t y, size_t z) {
    return x * chunks_size.y * chunks_size.z + z * chunks_size.y + y;
}

