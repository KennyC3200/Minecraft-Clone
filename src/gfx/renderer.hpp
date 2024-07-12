#pragma once

#include "../world/world.hpp"

class Renderer {
public:
    Renderer();
    ~Renderer();

    void init(World *world);
    void destroy();
    void render();
private:
    World *world;
};
