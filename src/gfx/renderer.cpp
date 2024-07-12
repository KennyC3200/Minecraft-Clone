#include "renderer.hpp"

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::init(World *world) {
    this->world = world;
}

void Renderer::destroy() {
}

void Renderer::render() {
    world->render();
}
