#include "keyboard.hpp"

void Keyboard::init(Window *window) {
    this->window = window;
}

void Keyboard::update() {
    for (int i = GLFW_KEY_SPACE; i < GLFW_KEY_LAST; i++) {
        int state = glfwGetKey(window->handle, i);
        if (state == GLFW_PRESS) {
            keys[i].down = true;
        }
        if (state == GLFW_RELEASE) {
            keys[i].down = false;
        }

        keys[i].pressed = keys[i].down && !keys[i].last;
        keys[i].last = keys[i].down;
    }
}
