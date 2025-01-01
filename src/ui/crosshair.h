#pragma once

#include "ui_component.h"
#include "../gfx/texture.h"

class Crosshair : public UIComponent {
public:
    void Init();
    void Render();

private:
    Texture texture;
};
