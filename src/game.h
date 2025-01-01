#pragma once

#include "gfx/window.h"
#include "gfx/renderer.h"
#include "input/keyboard.h"
#include "input/mouse.h"
#include "player/player.h"
#include "ui/hud/hud_manager.h"

class Game {
public:
    void Init();
    void Loop();
    void Destroy();

private:
    void Update();
    void Render();

    Window window;
    Renderer renderer;
    HudManager hud_manager;
    World world;

    Keyboard keyboard;
    Mouse mouse;

    Player player;
};
