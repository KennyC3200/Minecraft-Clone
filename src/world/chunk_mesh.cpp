#include "chunk_mesh.hpp"

ChunkMesh::ChunkMesh() {}

ChunkMesh::~ChunkMesh() {}

void ChunkMesh::init() {
    vao.init();
    vbo = VBO(GL_ARRAY_BUFFER, DYNAMIC_DRAW);
    ibo = VBO(GL_ELEMENT_ARRAY_BUFFER, DYNAMIC_DRAW);
}

void ChunkMesh::destroy() {
    vao.destroy();
}
