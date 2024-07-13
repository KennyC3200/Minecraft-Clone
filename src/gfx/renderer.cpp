#include "renderer.hpp"

void Renderer::init(World *world, Player *player) {
    this->world = world;
    this->player = player;

    flags.wireframe = false;
}

void Renderer::render() {
    if (flags.wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    world->render();
    player->render();
}
