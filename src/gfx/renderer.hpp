#pragma once

#include "../world/world.hpp"
#include "../player/player.hpp"

class Renderer {
public:
    void init(World *world, Player *player);
    void render();

    struct {
        bool wireframe;
    } flags;
private:
    World *world;
    Player *player;
};
