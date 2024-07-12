#include "vbo.hpp"

VBO::VBO() {}

VBO::~VBO() {
    glDeleteBuffers(1, &handle);
}

VBO::VBO(GLuint type, enum VBODrawType draw_type):
type(type),
draw_type(draw_type)
{
    glGenBuffers(1, &handle);
}

void VBO::bind() {
    glBindBuffer(type, handle);
}

void VBO::buffer(size_t size, void *data) {
    bind();
    glBufferData(type, size, data, draw_type);
}
