#pragma once

#include "gfx/window.hpp"
#include "gfx/renderer.hpp"

class Game {
public:
    Game();
    ~Game();

    void init();
    void destroy();
private:
    void loop();

    Window window;
    Renderer renderer;
    World world;
};
