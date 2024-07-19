#pragma once

#include "ui_component.hpp"

class Crosshair : public UIComponent {
public:
    void init() override;
    void render() override;
};
