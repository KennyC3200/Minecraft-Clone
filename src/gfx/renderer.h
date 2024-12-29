#pragma once

#include "../world/world.h"
#include "../player/player.h"

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
