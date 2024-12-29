#include "vao.h"

VAO::VAO() {}

VAO::~VAO() {}

void VAO::init() {
    glGenVertexArrays(1, &handle);
}

void VAO::destroy() {
    glDeleteVertexArrays(1, &handle);
}

void VAO::bind() {
    glBindVertexArray(handle);
}

void VAO::attr(
    VBO vbo, 
    GLuint location, GLint size, GLenum type, GLsizei stride, size_t offset) 
{
    // glVertexAttribPointer takes data from currently bound VBO
    vbo.bind();
    bind();

    glVertexAttribPointer(location, size, type, GL_FALSE, stride, (void*) offset);
    glEnableVertexAttribArray(location);
}
