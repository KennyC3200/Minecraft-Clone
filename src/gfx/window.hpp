#pragma once

#include "gfx.hpp"

class Window {
public:
    Window();
    ~Window();

    void init();
    void destroy();

    GLFWwindow *handle;

    glm::vec<2, int> size;
};
