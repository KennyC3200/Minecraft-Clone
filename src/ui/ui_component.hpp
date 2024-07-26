#pragma once

#include "../gfx/gfx.hpp"
#include "../gfx/window.hpp"
#include "../gfx/shader.hpp"
#include "../gfx/vbo.hpp"
#include "../gfx/vao.hpp"

class UIComponent {
public:
    static void init(Window *window);
    static void destroy();

    virtual void init();
    virtual void render();

    static Shader shader;
    static VAO vao;
    static VBO vbo, ibo;

    static Window *window;

    bool toggled;
};
