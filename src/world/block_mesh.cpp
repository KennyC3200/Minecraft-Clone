#include "block_mesh.hpp"

Shader BlockMesh::shader;

BlockMesh::BlockMesh() {}

BlockMesh::~BlockMesh() {}

BlockMesh::BlockMesh(Face faces[6]) {
    for (int i = 0; i < 6; i++) {
        this->faces[i] = faces[i];
    }
}

void BlockMesh::init() {
    shader.init("res/shaders/block.vs", "res/shaders/block.fs");
}
