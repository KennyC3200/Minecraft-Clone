#pragma once

#include "gfx.hpp"

enum VBODrawType {
    DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
    STATIC_DRAW = GL_STATIC_DRAW
};

class VBO {
public:
    VBO();
    ~VBO();
    VBO(GLuint type, enum VBODrawType draw_type);

    void bind();
    void buffer(size_t size, void *data);

    GLuint handle, type;
    enum VBODrawType draw_type;
};
