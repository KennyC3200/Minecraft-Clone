#pragma once

#include "gfx.h"

class Window {
public:
    void Init(glm::ivec2 size);
    void Destroy();
    void Update();

    GLFWwindow* GetHandle();

    glm::ivec2 GetSize();
    glm::vec2 GetPixelUnit();

    float GetFPS();
    float GetTimeDelta();

private:
    GLFWwindow* handle;

    glm::ivec2 size;

    float fps, time_previous, time_current, time_delta;
};
