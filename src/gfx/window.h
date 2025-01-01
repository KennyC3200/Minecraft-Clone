#pragma once

#include "gfx.h"

class Window {
public:
    Window();
    ~Window();

    void Init();
    void Destroy();
    void Update();

    GLFWwindow *handle;

    glm::vec<2, int> size;

    float fps, time_previous, time_current, time_delta;
};
