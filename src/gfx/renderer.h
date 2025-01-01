#pragma once

#include "../world/world.h"
#include "../player/player.h"

class Renderer {
public:
    void Init(World* world, Player* player);
    void Render();

    struct {
        bool wireframe;
    } flags;

private:
    void RenderWorld();
    void RenderUI();

    World* world;
    Player* player;
};
