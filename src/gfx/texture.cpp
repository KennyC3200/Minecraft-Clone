#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void Texture::Init(std::string path, std::string fs_name, GLint tex_format, GLint src_format)
{
    this->fs_name = fs_name;

    glGenTextures(1, &handle);
    Bind();

    // no interpolation
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // OpenGL has texture coordinates with (0, 0) on bottom left
    stbi_set_flip_vertically_on_load(true);
    int channels;
    unsigned char *data = stbi_load(path.c_str(), &size.x, &size.y, &channels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, tex_format, size.x, size.y, 0, src_format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        fprintf(stderr, "Error creating texture\n");
    }
    stbi_image_free(data);
}

void Texture::Destroy() {
    glDeleteTextures(1, &handle);
}

void Texture::Bind() {
    glBindTexture(GL_TEXTURE_2D, handle);
}

GLuint Texture::GetHandle() {
    return handle;
}

std::string& Texture::GetFSName() {
    return fs_name;
}

glm::ivec2 Texture::GetSize() {
    return size;
}
