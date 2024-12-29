#pragma once

#include "ui_component.h"
#include "../gfx/texture.h"

class Crosshair : public UIComponent {
public:
    void init();
    void render();
private:
    Texture texture;
};
