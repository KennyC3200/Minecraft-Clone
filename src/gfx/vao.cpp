#include "vao.h"

VAO::VAO() {}

VAO::~VAO() {}

void VAO::Init() {
    glGenVertexArrays(1, &handle);
}

void VAO::Destroy() {
    glDeleteVertexArrays(1, &handle);
}

void VAO::Bind() {
    glBindVertexArray(handle);
}

void VAO::AttribPointer(
    VBO vbo,
    GLuint location, GLint size, GLenum type, GLsizei stride, size_t offset)
{
    // glVertexAttribPointer takes data from currently bound VBO
    vbo.Bind();
    Bind();

    glVertexAttribPointer(location, size, type, GL_FALSE, stride, (void*) offset);
    glEnableVertexAttribArray(location);
}

void VAO::AttribIPointer(
    VBO vbo,
    GLuint location, GLint size, GLenum type, GLsizei stride, size_t offset)
{
    // glVertexAttribIPointer takes data from currently bound VBO
    vbo.Bind();
    Bind();

    glVertexAttribIPointer(location, size, type, stride, (void*) offset);
    glEnableVertexAttribArray(location);
}
