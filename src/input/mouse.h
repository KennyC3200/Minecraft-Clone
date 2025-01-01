#pragma once

#include "input.h"

class Mouse : public Input {
public:
    /* Init the mouse */
    void Init(Window* window) override {
        Input::Init(window, GLFW_MOUSE_BUTTON_1, GLFW_MOUSE_BUTTON_LAST);

        toggled = false;
        first_move = true;
    }

    /* Update the mouse */
    void Update() override {
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

        Input::Update();

        glfwSetInputMode(
            window->handle, 
            GLFW_CURSOR, 
            toggled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED
        );
    }

    glm::vec2 GetPosition();
    glm::vec2 GetPositionDelta();

protected:
    /* Get the button state
     * Required by Input class
     * */
    int GetButtonState(int button) override {
        return glfwGetMouseButton(window->handle, button);
    }

    glm::vec2 position;
    glm::vec2 position_delta;

private:
    bool first_move;
};
