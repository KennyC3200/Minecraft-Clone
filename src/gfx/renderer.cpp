#include "renderer.h"

void Renderer::Init(World* world, Player* player, HudManager* hud_manager) {
    this->world = world;
    this->player = player;
    this->hud_manager = hud_manager;

    flags.wireframe = false;

    // Blend for alpha channel
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 3D depth
    glEnable(GL_DEPTH_TEST);
}

void Renderer::Render() {
    if (flags.wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    RenderWorld();
    RenderUI();
}

void Renderer::RenderWorld() {
    // Bind the chunk shader
    ChunkMesh::shader.Bind();

    // Bind the view and projection matrices
    ChunkMesh::shader.UniformMat4("view", player->GetCamera().GetView());
    ChunkMesh::shader.UniformMat4("projection", player->GetCamera().GetProjection());

    // Render the world
    ChunkMesh::shader.UniformTexture2D(BlockMesh::GetAtlas(), 0);
    world->Render();
}

void Renderer::RenderUI() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    hud_manager->Render();
}
