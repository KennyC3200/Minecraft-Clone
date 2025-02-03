#pragma once

#include "vbo.h"

class VAO {
public:
    VAO();
    ~VAO();

    void Init();
    void Destroy();
    void Bind();
    void AttribPointer(
        VBO vbo,
        GLuint location, GLint size, GLenum type, GLsizei stride, size_t offset);
    void AttribIPointer(
        VBO vbo,
        GLuint location, GLint size, GLenum type, GLsizei stride, size_t offset);
    inline GLuint GetHandle() { return handle; }

private:
    GLuint handle;
};
