#pragma once

#include "gfx.h"
#include "vbo.h"

class VAO {
public:
    VAO();
    ~VAO();

    void init();
    void destroy();
    void bind();
    void attr(
        VBO vbo, 
        GLuint location, GLint size, GLenum type, GLsizei stride, size_t offset);

    GLuint handle;
};
