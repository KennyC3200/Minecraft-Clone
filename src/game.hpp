#pragma once

#include "gfx/window.hpp"
#include "gfx/renderer.hpp"

class Game {
public:
    Game();
    ~Game();

    void init();
    void loop();
    void destroy();
private:
    Window window;
    Renderer renderer;
    World world;
};
