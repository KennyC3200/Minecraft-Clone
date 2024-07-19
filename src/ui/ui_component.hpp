#pragma once

#include "../gfx/gfx.hpp"
#include "../gfx/window.hpp"
#include "../gfx/texture.hpp"
#include "../gfx/shader.hpp"
#include "../gfx/vbo.hpp"
#include "../gfx/vao.hpp"

enum UITextures {
    UI_TEXTURE_CROSSHAIR = 0,
    UI_TEXTURE_HOTBAR,
    UI_TEXTURE_LAST,
};

class UIComponent {
public:
    static void init(Window *window);
    static void destroy();

    virtual void init();
    virtual void render();

    static Shader shader;
    static Texture textures[UI_TEXTURE_LAST];
    static VAO vao;
    static VBO vbo, ibo;

    static Window *window;

    bool toggled;
};
