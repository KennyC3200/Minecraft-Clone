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

    render_world();
    render_ui();
}

void Renderer::render_world() {
    // Bind the chunk shader
    ChunkMesh::shader.bind();

    // Bind the view and projection matrices
    ChunkMesh::shader.uniform_mat4("view", player->get_camera().get_view());
    ChunkMesh::shader.uniform_mat4("projection", player->get_camera().get_projection());

    // Render the world
    ChunkMesh::shader.uniform_texture_2d(BlockMesh::GetAtlas().texture, 0);
    world->Render();
}

// TODO
void Renderer::render_ui() {
}
