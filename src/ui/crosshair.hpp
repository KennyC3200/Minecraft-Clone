#pragma once

#include "ui_component.hpp"
#include "../gfx/texture.hpp"

class Crosshair : public UIComponent {
public:
    void init() override;
    void render() override;
private:
    Texture texture;
};
