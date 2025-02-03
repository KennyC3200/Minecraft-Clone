#pragma once

#include "gfx.h"

class Texture {
public:
    void Init(std::string path, const std::string& fs_name, GLint tex_format, GLint src_format);
    void Destroy();
    void Bind();

    inline GLuint GetHandle() { return handle; }
    inline const std::string& GetFSName() { return fs_name; }
    inline glm::ivec2 GetSize() { return size; }

protected:
    GLuint handle;
    std::string fs_name;
    glm::ivec2 size;
};
