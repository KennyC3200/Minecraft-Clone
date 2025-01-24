#pragma once

#include "gfx.h"

class Texture {
public:
    void Init(std::string path, const std::string& fs_name, GLint tex_format, GLint src_format);
    void Destroy();
    void Bind();

    GLuint GetHandle();
    const std::string& FSName();
    glm::ivec2 Size();

protected:
    GLuint handle;
    std::string fs_name;
    glm::ivec2 size;
};
