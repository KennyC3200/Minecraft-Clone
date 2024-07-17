#include "world.hpp"

void World::init(Player *player) {
    this->player = player;

    Block::init();
    Chunk::init(player);

    chunks_size = 4;
    chunks = new Chunk*[chunks_size];
    chunks[0] = new Chunk({0, 0, 0});
    chunks[1] = new Chunk({1, 0, 0});
    chunks[2] = new Chunk({0, 0, 1});
    chunks[3] = new Chunk({1, 0, 1});
}

void World::destroy() {
    for (size_t i = 0; i < chunks_size; i++) {
        delete chunks[i];
    }
    delete[] chunks;
}

void World::render() {
    BlockMesh::shader.bind();
    BlockMesh::shader.uniform_texture_2d(Block::atlas.texture, 0);

    for (size_t i = 0; i < chunks_size; i++) {
        chunks[i]->render();
    }
}
