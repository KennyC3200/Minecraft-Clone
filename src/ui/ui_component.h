#pragma once

#include "../gfx/gfx.h"
#include "../gfx/window.h"
#include "../gfx/shader.h"
#include "../gfx/vbo.h"
#include "../gfx/vao.h"

class UIComponent {
public:
    static void Init(Window* window);
    static void Destroy();

    static Shader shader;
    static VAO vao;
    static VBO vbo, ibo;

    static Window* window;

    bool toggled;
};
