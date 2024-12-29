#pragma once

#include "gfx.h"

class Window {
public:
    Window();
    ~Window();

    void init();
    void destroy();
    void update();

    GLFWwindow *handle;

    glm::vec<2, int> size;

    float fps, time_previous, time_current, time_delta;
};
