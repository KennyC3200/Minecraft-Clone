#include "world.hpp"

World::World() {}

World::~World() {}

void World::init() {
    Block::init();

    Chunk *chunk = new Chunk(glm::vec<2, int>(0, 0));
    chunks.push_back(chunk);
}

void World::destroy() {
    for (size_t i = 0; i < chunks.size(); i++) {
        delete chunks[i];
    }
}

void World::render() {
    for (auto &chunk : chunks) {
        chunk->render();
    }
}
