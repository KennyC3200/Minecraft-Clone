#pragma once

#include "input.h"

class Keyboard : public Input {
public:
    void Init(Window* window) override {
        Input::Init(window, GLFW_KEY_SPACE, GLFW_KEY_LAST);
    }

protected:
    /* Get the button state
     * Required by Input class
     * */
    int GetButtonState(int button) override {
        return glfwGetKey(window->GetHandle(), button);
    }
};
