#pragma once

#include <vector>

#include "chunk.hpp"
#include "../player/player.hpp"

class World {
public:
    void init(Player *player);
    void destroy();
    void render();

    std::vector<Chunk*> chunks;
private:
    Player *player;
};
