#pragma once

#include "../world/world.hpp"

class Renderer {
public:
    Renderer();
    ~Renderer();

    void init();
    void render();
    void destroy();
private:
    World *world;
};
