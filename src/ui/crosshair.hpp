#pragma once

#include "../gfx/gfx.hpp"
#include "../gfx/window.hpp"
#include "../gfx/texture.hpp"
#include "../gfx/shader.hpp"

class Crosshair {
public:
    void init(Window *window);
    void render();

    bool toggled;
private:
    Window *window;
    Shader shader;
    Texture texture;
};
