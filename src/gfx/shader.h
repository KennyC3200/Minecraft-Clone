#pragma once

#include "texture.h"

class Shader {
public:
    void Init(const std::string& vs_path, const std::string& fs_path);
    void Destroy();
    GLuint GetHandle();
    void Bind();

    void UniformTexture2D(Texture& tex, unsigned int unit);
    void UniformTexture2D(Texture& tex, const std::string& fs_name, unsigned int unit);
    void UniformMat4(const std::string& name, glm::mat4& mat);
    void UniformVec3(const std::string& name, glm::vec3& vec);
    void UniformIVec3(const std::string& name, glm::ivec3& vec);

private:
    GLuint Compile(const std::string& path, GLuint type);

    GLuint handle;
};
