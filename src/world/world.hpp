#pragma once

#include <vector>

#include "chunk.hpp"
#include "../player/player.hpp"

class World {
public:
    void init(Player *player);
    void destroy();
    void render();

    Chunk **chunks;
    glm::vec<3, size_t> chunks_size;
private:
    size_t chunks_idx(size_t x, size_t y, size_t z);
    size_t chunks_size_magnitude();

    Player *player;
};
