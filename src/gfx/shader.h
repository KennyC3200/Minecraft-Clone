#pragma once

#include "gfx.h"
#include "texture.h"

#include <fstream>
#include <sstream>

class Shader {
public:
    void Init(std::string vs_path, std::string fs_path);
    void Destroy();
    void Bind();
    void UniformTexture2D(Texture tex, unsigned int unit);
    void UniformTexture2D(Texture tex, std::string fs_name, unsigned int unit);
    void UniformMat4(std::string name, glm::mat4 mat4);
    GLuint GetHandle();

private:
    GLuint Compile(std::string path, GLuint type);

    GLuint handle;
};
