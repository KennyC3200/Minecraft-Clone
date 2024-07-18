#include "world.hpp"

void World::init(Player *player) {
    this->player = player;

    Block::init();
    Chunk::init();

    chunks_size = 125;
    chunks = new Chunk*[chunks_size];
    for (int x = 0; x < 5; x++) {
        for (int z = 0; z < 5; z++) {
            for (int y = 0; y < 5; y++) {
                chunks[x * 25 + z * 5 + y] = new Chunk({x, y, z});
            }
        }
    }
    for (int x = 0; x < 5; x++) {
        for (int z = 0; z < 5; z++) {
            for (int y = 0; y < 5; y++) {
                Chunk *neighbors[6];
                neighbors[NORTH] = z - 1 >= 0 ? chunks[x * 25 + (z - 1) * 5 + y] : nullptr;
                neighbors[SOUTH] = z + 1 <  5 ? chunks[x * 25 + (z + 1) * 5 + y] : nullptr;
                neighbors[EAST]  = x + 1 <  5 ? chunks[(x + 1) * 25 + z * 5 + y] : nullptr;
                neighbors[WEST]  = x - 1 >= 0 ? chunks[(x - 1) * 25 + z * 5 + y] : nullptr;
                neighbors[UP]    = y + 1 <  5 ? chunks[x * 25 + z * 5 + (y + 1)] : nullptr;
                neighbors[DOWN]  = y - 1 >= 0 ? chunks[x * 25 + z * 5 + (y - 1)] : nullptr;
                chunks[x * 25 + z * 5 + y]->neighbors_set(neighbors);
            }
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
