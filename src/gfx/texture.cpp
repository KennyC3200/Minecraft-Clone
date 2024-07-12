#include "texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture() {}

Texture::~Texture() {
    glDeleteTextures(1, &handle);
}

Texture::Texture(std::string path, std::string fs_name, GLint tex_format, GLint src_format):
fs_name(fs_name)
{
    glGenTextures(1, &handle);
    bind();

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

void Texture::bind() {
}
