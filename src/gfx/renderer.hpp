#pragma once

#include "../world/world.hpp"
#include "../player/player.hpp"

class Renderer {
public:
    Renderer();
    ~Renderer();

    void init(World *world, Player *player);
    void destroy();
    void render();
private:
    World *world;
    Player *player;
};
