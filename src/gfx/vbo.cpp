#include "vbo.hpp"

VBO::VBO() {}

VBO::~VBO() {}

void VBO::init(GLuint type, enum VBODrawType draw_type) {
    this->type = type;
    this->draw_type = draw_type;
    glGenBuffers(1, &handle);
}

void VBO::destroy() {
    glDeleteBuffers(1, &handle);
}

void VBO::bind() {
    glBindBuffer(type, handle);
}

void VBO::buffer(size_t size, void *data) {
    bind();
    glBufferData(type, size, data, draw_type);
}
