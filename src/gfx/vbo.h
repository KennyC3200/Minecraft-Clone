#pragma once

#include "gfx.h"

class VBO {
public:
    VBO();
    ~VBO();

    void Init(GLuint type, GLuint draw_type);
    void Destroy();
    void Bind();
    void Buffer(size_t size, void *data);

    GLuint GetHandle();

private:
    GLuint handle;
    GLuint type, draw_type;
};
