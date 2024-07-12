#include "block_mesh.hpp"

Shader BlockMesh::shader;

BlockMesh::BlockMesh() {}

BlockMesh::~BlockMesh() {}

BlockMesh::BlockMesh(glm::vec2 uv_min, glm::vec2 uv_max):
uv_min(uv_min),
uv_max(uv_max) 
{}

void BlockMesh::init() {
    shader = Shader("res/shaders/block.vs", "res/shaders/block.fs");
}
