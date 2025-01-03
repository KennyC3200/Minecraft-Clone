#pragma once

#include "gfx.h"
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
    GLuint GetHandle();

private:
    GLuint handle;
};
