#include "renderer.h"

void Renderer::init(World *world, Player *player) {
    this->world = world;
    this->player = player;

    flags.wireframe = false;

    // Blend for alpha channel
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 3D depth
    glEnable(GL_DEPTH_TEST);
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
