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
    size_t chunks_size;
private:
    Player *player;
};
