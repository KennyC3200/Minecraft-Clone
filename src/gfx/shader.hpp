#pragma once

#include <fstream>
#include <sstream>

#include "gfx.hpp"
#include "texture.hpp"

class Shader {
public:
    void init(std::string vs_path, std::string fs_path);
    void destroy();
    void bind();
    void uniform_texture_2d(Texture tex, unsigned int unit);
    void uniform_texture_2d(Texture tex, std::string fs_name, unsigned int unit);
    void uniform_mat4(std::string name, glm::mat4 mat4);

    GLuint handle;
private:
    GLuint compile(std::string path, GLuint type);
};
