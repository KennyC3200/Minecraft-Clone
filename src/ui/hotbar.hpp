#pragma once

#include "../gfx/gfx.hpp"
#include "../gfx/texture.hpp"

class Hotbar {
public:
    void init();
    void render();

    bool toggled;
private:
    Texture texture;
};
