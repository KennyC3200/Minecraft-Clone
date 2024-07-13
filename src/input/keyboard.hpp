#pragma once

#include "input.hpp"

class Keyboard {
public:
    void init(Window *window);
    void update();

    Button keys[GLFW_KEY_LAST];
private:
    Window *window;
};
