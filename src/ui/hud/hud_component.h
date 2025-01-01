#pragma once

#include "../../gfx/gfx.h"
#include "../../gfx/window.h"
#include "../../gfx/shader.h"
#include "../../gfx/vbo.h"
#include "../../gfx/vao.h"

class HudComponent {
public:
    virtual void Mesh() = 0;
    virtual void Render() = 0;

    bool meshed;
    bool toggled;

protected:
    friend class HudManager;

    static void Init(Window* window);
    static void Destroy();

    static Window* window;
    static Shader shader;
    static VAO vao;
    static VBO vbo;
    static VBO ibo;
};
