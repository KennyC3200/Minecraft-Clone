#include "vbo.h"

VBO::VBO() {}

VBO::~VBO() {}

void VBO::Init(GLuint type, GLuint draw_type) {
    this->type = type;
    this->draw_type = draw_type;
    glGenBuffers(1, &handle);
}

void VBO::Destroy() {
    glDeleteBuffers(1, &handle);
}

void VBO::Bind() {
    glBindBuffer(type, handle);
}

void VBO::Buffer(size_t size, void *data) {
    Bind();
    glBufferData(type, size, data, draw_type);
}
