#pragma once

#include "../util/util.hpp"
#include "../gfx/window.hpp"
#include "../input/keyboard.hpp"
#include "../input/mouse.hpp"
#include "camera.hpp"

class Player {
public:
    void init(Window *window, Keyboard *keyboard, Mouse *mouse);
    void update();
    void render();

    glm::vec2 position;
    Camera camera;
private:
    Window *window;
    Keyboard *keyboard;
    Mouse *mouse;
};
