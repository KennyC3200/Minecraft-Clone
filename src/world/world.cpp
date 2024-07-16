#include "world.hpp"

void World::init(Player *player) {
    this->player = player;

    Block::init();
    Chunk::init(player);

    chunks_count = 2;
    chunks = new Chunk*[chunks_count];
    chunks[0] = new Chunk(glm::vec<3, int>(0, 0, 0));
    chunks[1] = new Chunk(glm::vec<3, int>(1, 0, 0));
}

void World::destroy() {
    for (size_t i = 0; i < chunks_count; i++) {
        delete chunks[i];
    }
    delete[] chunks;
}

void World::render() {
    for (size_t i = 0; i < chunks_count; i++) {
        chunks[i]->render();
    }
}
