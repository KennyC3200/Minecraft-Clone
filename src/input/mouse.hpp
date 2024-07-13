#pragma once

#include "input.hpp"

class Mouse {
public:
    void init(Window *window, bool toggled);
    void update();

    glm::vec2 position, position_delta;
    Button keys[GLFW_MOUSE_BUTTON_LAST];
    bool toggled;
private:
    Window *window;
    bool first_move;
};
