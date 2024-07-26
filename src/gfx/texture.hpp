#pragma once 

#include "gfx.hpp"

class Texture {
public:
    void init(std::string path, std::string fs_name, GLint tex_format, GLint src_format);
    void destroy();
    void bind();

    GLuint handle;
    std::string fs_name;
    glm::vec<2, int> size;
};
