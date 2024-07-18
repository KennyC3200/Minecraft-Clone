#include "world.hpp"

void World::init(Player *player) {
    this->player = player;

    Block::init();
    Chunk::init();

    chunks_size = 100;
    chunks = new Chunk*[chunks_size];
    for (int x = 0; x < 10; x++) {
        for (int z = 0; z < 10; z++) {
            chunks[x * 10 + z] = new Chunk({x, 0, z});
        }
    }
    for (int x = 0; x < 10; x++) {
        for (int z = 0; z < 10; z++) {
            Chunk *neighbors[6];
            neighbors[NORTH] = z - 1 < 10 ? chunks[z + 1] : nullptr;
            neighbors[SOUTH] = z + 1 < 10 ? chunks[z + 1] : nullptr;
            neighbors[EAST]  = x + 1 < 10 ? chunks[x + 1] : nullptr;
            neighbors[WEST]  = x - 1 > 0  ? chunks[x - 1] : nullptr;
            neighbors[UP]    = nullptr;
            neighbors[DOWN]  = nullptr;
            chunks[x * 10 + z]->neighbors_set(neighbors);
        }
    }
}

void World::destroy() {
    for (size_t i = 0; i < chunks_size; i++) {
        delete chunks[i];
    }
    delete[] chunks;
}

void World::render() {
    ChunkMesh::shader.bind();
    ChunkMesh::shader.uniform_texture_2d(Block::atlas.texture, 0);

    for (size_t i = 0; i < chunks_size; i++) {
        chunks[i]->render();
    }
}
