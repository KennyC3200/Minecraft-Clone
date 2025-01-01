#include "shader.h"

void Shader::Init(std::string vs_path, std::string fs_path) {
    handle = glCreateProgram();
    GLuint vs_handle = Compile(vs_path, GL_VERTEX_SHADER);
    GLuint fs_handle = Compile(fs_path, GL_FRAGMENT_SHADER);

    glAttachShader(handle, vs_handle);
    glAttachShader(handle, fs_handle);
    glLinkProgram(handle);
    glValidateProgram(handle);

    int result;
    glGetProgramiv(handle, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        int len;
        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &len);
        char msg[len];
        glGetProgramInfoLog(handle, len, &len, msg);
        fprintf(stderr, "Error linking program: %s\n", msg);
    }

    glDeleteShader(vs_handle);
    glDeleteShader(fs_handle);
}

void Shader::Destroy() {
    glDeleteProgram(handle);
}

void Shader::Bind() {
    glUseProgram(handle);
}

void Shader::UniformTexture2D(Texture tex, unsigned int unit) {
    glActiveTexture(GL_TEXTURE0 + unit);
    tex.Bind();
    glUniform1i(glGetUniformLocation(handle, tex.GetFSName().c_str()), unit);
}

void Shader::UniformTexture2D(Texture tex, std::string fs_name, unsigned int unit) {
    glActiveTexture(GL_TEXTURE0 + unit);
    tex.Bind();
    glUniform1i(glGetUniformLocation(handle, fs_name.c_str()), unit);
}

void Shader::UniformMat4(std::string name, glm::mat4 mat4) {
    glUniformMatrix4fv(
        glGetUniformLocation(handle, name.c_str()), 
        1, GL_FALSE, 
        glm::value_ptr(mat4));
}

GLuint Shader::Compile(std::string path, GLuint type) {
    std::ifstream file;
    std::string text;
    std::stringstream stream;

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(path);
        stream << file.rdbuf();
        file.close();
        text = stream.str();
    } catch (std::ifstream::failure e) {
        std::cout << "Error compiling shader\n";
    }

    GLuint handle = glCreateShader(type);
    const char *text_src = text.c_str();
    int text_len = text.length();
    glShaderSource(handle, 1, &text_src, &text_len);
    glCompileShader(handle);

    int result;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int len;
        glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &len);
        char msg[len];
        glGetShaderInfoLog(handle, len, &len, msg);
        std::cout << "Error compiling shader " << path << ": " << msg << '\n';
    }

    return handle;
}
