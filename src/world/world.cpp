#include "world.hpp"

void World::init(Player *player) {
    this->player = player;

    Block::init();
    Chunk::init();

    chunks_size = 100;
    chunks = new Chunk*[chunks_size];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            chunks[i * 10 + j] = new Chunk({i, 0, j});
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
