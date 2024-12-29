#pragma once

#include "input.h"

class Keyboard : public Input {
public:
    void init(Window *window) override {
        Input::init(window, GLFW_KEY_SPACE, GLFW_KEY_LAST);
    }

protected:
    /* Get the button state
     * Required by Input class
     * */
    int get_button_state(int button) override {
        return glfwGetKey(window->handle, button);
    }
};
