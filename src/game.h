#pragma once

#include "gfx/window.h"
#include "gfx/renderer.h"
#include "input/keyboard.h"
#include "input/mouse.h"
#include "player/player.h"
#include "ui/hud/hud_manager.h"
#include "ui/gui/gui_manager.h"

class Game {
public:
    void Init();
    void Loop();
    void Destroy();

private:
    void Update();
    void Render();

    bool running;

    Window window;
    Renderer renderer;

    HudManager hud_manager;
    GuiManager gui_manager;

    Keyboard keyboard;
    Mouse mouse;

    World world;
    Player player;
};
