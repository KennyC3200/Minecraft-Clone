#include "mouse.hpp"

void Mouse::init(Window *window) {
    this->window = window;
    toggled = false;
    first_move = true;
}

void Mouse::update() {
    double x, y;
    glfwGetCursorPos(window->handle, &x, &y);

    if (first_move) {
        position.x = x;
        position.y = y;
        first_move = false;
    }
    position_delta.x = x - position.x;
    position_delta.y = position.y - y;
    position.x = x;
    position.y = y;

    for (int i = GLFW_MOUSE_BUTTON_1; i < GLFW_MOUSE_BUTTON_LAST; i++) {
        int state = glfwGetMouseButton(window->handle, i);
        if (state == GLFW_PRESS) {
            keys[i].down = true;
        }
        if (state == GLFW_RELEASE) {
            keys[i].down = false;
        }

        keys[i].pressed = keys[i].down && !keys[i].last;
        keys[i].last = keys[i].down;
    }

    glfwSetInputMode(
        window->handle, 
        GLFW_CURSOR, 
        toggled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}
