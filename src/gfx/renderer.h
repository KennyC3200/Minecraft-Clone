#pragma once

#include "../world/world.h"
#include "../player/player.h"
#include "../ui/hud/hud_manager.h"

class Renderer {
public:
    void Init(World* world, Player* player, HudManager* hud_manager);
    void Render();

    struct {
        bool wireframe;
    } flags;

private:
    void RenderWorld();
    void RenderUI();

    World* world;
    Player* player;
    HudManager* hud_manager;
};
