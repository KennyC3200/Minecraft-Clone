#pragma once

#include "ui_component.hpp"
#include "../gfx/texture.hpp"

class Crosshair : public UIComponent {
public:
    void init();
    void render();
private:
    Texture texture;
};
