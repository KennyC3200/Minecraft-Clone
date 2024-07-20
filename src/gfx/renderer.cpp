#include "renderer.hpp"

void Renderer::init(World *world, Player *player) {
    this->world = world;
    this->player = player;

    flags.wireframe = false;

    // blend for alpha channel
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 3d depth
    glEnable(GL_DEPTH_TEST);
}

void Renderer::render() {
    if (flags.wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    world->render();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    player->render();
}
