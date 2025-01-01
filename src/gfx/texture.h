#pragma once 

#include "gfx.h"

class Texture {
public:
    void Init(std::string path, std::string fs_name, GLint tex_format, GLint src_format);
    void Destroy();
    void Bind();

    GLuint GetHandle();
    std::string& GetFSName();
    glm::ivec2 GetSize();

private:
    GLuint handle;
    std::string fs_name;
    glm::ivec2 size;
};
