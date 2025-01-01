#pragma once

#include "../../gfx/gfx.h"
#include "../../player/player.h"
#include "crosshair.h"
#include "hotbar.h"

class HudManager {
public:
    void Init(Window* window, Player* player);
    void Destroy();
    void Render();

    static void MeshCrosshair();
    static void MeshHotbar();

private:
    static Crosshair crosshair;
    static Hotbar hotbar;
};
