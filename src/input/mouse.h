#pragma once

#include "input.h"

class Mouse : public Input {
public:
    /* Init the mouse */
    void init(Window *window) override {
        Input::init(window, GLFW_MOUSE_BUTTON_1, GLFW_MOUSE_BUTTON_LAST);

        toggled = false;
        first_move = true;
    }

    /* Update the mouse */
    void update() override {
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

        Input::update();

        glfwSetInputMode(
            window->handle, 
            GLFW_CURSOR, 
            toggled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED
        );
    }

    glm::vec2 get_position();
    glm::vec2 get_position_delta();

protected:
    /* Get the button state
     * Required by Input class
     * */
    int get_button_state(int button) override {
        return glfwGetMouseButton(window->handle, button);
    }

    glm::vec2 position;
    glm::vec2 position_delta;

private:
    bool first_move;
};
