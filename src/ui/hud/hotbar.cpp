#include "hotbar.h"

void Hotbar::Init(Player* player) {
    this->player = player;

    toggled = true;
    atlas.Init("../res/images/hotbar.png", "tex", {22, 22});
}

void Hotbar::MeshItem(glm::vec2 p1, glm::vec2 p2, BlockID block_id) {
    glm::vec2 uv_min = BlockMesh::Get(block_id).GetFace(NORTH).uv_min;
    glm::vec2 uv_max = BlockMesh::Get(block_id).GetFace(NORTH).uv_max;

    // Append the indices
    // IMPORTANT: Calculate the vertex offset for the indices since more vertices have been added
    unsigned int vertex_offset = vertices[ITEM_MESH].size() / 4;
    unsigned int indices[] = {
        vertex_offset + 0, vertex_offset + 1, vertex_offset + 3,
        vertex_offset + 1, vertex_offset + 2, vertex_offset + 3
    };
    this->indices[ITEM_MESH].insert(
        this->indices[ITEM_MESH].end(), 
        std::begin(indices), 
        std::end(indices));

    float vertices[] = {
        p1.x, p2.y, uv_min.x, 1 - uv_min.y,
        p1.x, p1.y, uv_min.x, 1 - uv_max.y,
        p2.x, p1.y, uv_max.x, 1 - uv_max.y,
        p2.x, p2.y, uv_max.x, 1 - uv_min.y
    };
    this->vertices[ITEM_MESH].insert(
        this->vertices[ITEM_MESH].end(), 
        std::begin(vertices), 
        std::end(vertices));
}

void Hotbar::MeshFrame(glm::vec2 p1, glm::vec2 p2, bool active) {
    int u_offset = active ? 1 : 0;

    // Append the indices
    // IMPORTANT: Calculate the vertex offset for the indices since more vertices have been added
    unsigned int vertex_offset = vertices[FRAME_MESH].size() / 4;
    unsigned int indices[] = {
        vertex_offset + 0, vertex_offset + 1, vertex_offset + 3,
        vertex_offset + 1, vertex_offset + 2, vertex_offset + 3
    };
    this->indices[FRAME_MESH].insert(
        this->indices[FRAME_MESH].end(), 
        std::begin(indices), 
        std::end(indices));

    glm::vec2 uv1 = atlas.SpriteUV(1 + u_offset, 0);
    glm::vec2 uv2 = atlas.SpriteUV(1 + u_offset, 1);
    glm::vec2 uv3 = atlas.SpriteUV(u_offset, 1);
    glm::vec2 uv4 = atlas.SpriteUV(u_offset, 0);

    // Append the vertices
    float vertices[] = {
        p1.x, p2.y, uv1.x, uv1.y,
        p1.x, p1.y, uv2.x, uv2.y,
        p2.x, p1.y, uv3.x, uv3.y,
        p2.x, p2.y, uv4.x, uv4.y
    };
    this->vertices[FRAME_MESH].insert(
        this->vertices[FRAME_MESH].end(), 
        std::begin(vertices), 
        std::end(vertices));
}
