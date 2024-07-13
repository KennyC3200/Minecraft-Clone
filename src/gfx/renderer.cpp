#include "renderer.hpp"

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::init(World *world, Player *player) {
    this->world = world;
    this->player = player;
}

void Renderer::destroy() {
}

void Renderer::render() {
    world->render();
    player->render();
}
