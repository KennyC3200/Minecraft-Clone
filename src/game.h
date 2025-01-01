#pragma once

#include "gfx/window.h"
#include "gfx/renderer.h"
#include "input/keyboard.h"
#include "input/mouse.h"
#include "player/player.h"
#include "ui/ui.h"

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
    UI ui;
    World world;

    Keyboard keyboard;
    Mouse mouse;

    Player player;
};
