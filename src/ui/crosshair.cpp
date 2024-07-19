#include "crosshair.hpp"

void Crosshair::init(Window *window) {
    this->window = window;
    toggled = true;
    shader.init("res/shaders/texture_2d.vs", "res/shaders/texture_2d.fs");
    texture.init("res/images/crosshair.png", "tex", GL_RGBA, GL_RGBA);
}

void Crosshair::render() {
    shader.bind();
}
