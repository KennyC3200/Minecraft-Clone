#pragma once

#include "../gfx/window.h"

typedef struct {
    bool down;
    bool pressed;
    bool last;
} Button;

class Input {
public:
    virtual void init(Window *window) = 0;

    virtual void update() {
        for (int i = button_first; i < button_last; i++) {
            int state = get_button_state(i);
            if (state == GLFW_PRESS) {
                buttons[i].down = true;
            }
            if (state == GLFW_RELEASE) {
                buttons[i].down = false;
            }

            buttons[i].pressed = buttons[i].down && !buttons[i].last;
            buttons[i].last = buttons[i].down;
        }
    }

    virtual Button get_button(int button) {
        return buttons[button];
    }

    virtual bool get_toggled() {
        return toggled;
    }

    virtual void set_toggled(bool toggled) {
        this->toggled = toggled;
    }

protected:
    Window *window;
    int button_first, button_last;
    Button *buttons;
    bool toggled;

    void init(Window *window, int button_first, int button_last) {
        this->window = window;
        this->button_first = button_first;
        this->button_last = button_last;

        toggled = true;
        buttons = new Button[button_last];
    }

    virtual int get_button_state(int button) = 0;
};
