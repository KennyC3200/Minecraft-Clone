#pragma once

#include "../gfx/gfx.hpp"
#include "../gfx/window.hpp"
#include "../gfx/texture.hpp"

class UIComponent {
public:
    virtual void init();
    virtual void render();

    bool toggled;
};
