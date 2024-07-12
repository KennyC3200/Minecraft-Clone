#include "world.hpp"

World::World() {}

World::~World() {}

void World::init() {
    chunks.push_back(new Chunk(glm::vec<2, int>(0, 0)));
}

void World::destroy() {
    for (size_t i = 0; i < chunks.size(); i++) {
        delete chunks[i];
    }
}
