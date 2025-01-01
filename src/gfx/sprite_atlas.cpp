#include "sprite_atlas.h"

void SpriteAtlas::Init(const std::string& path, const std::string& fs_name, glm::vec2 sprite_size) {
    this->sprite_size = sprite_size;

    Texture::Init(path, fs_name, GL_RGBA, GL_RGBA);
    sprite_unit = sprite_size / glm::vec2(size);
    pixel_unit = 1.0f / glm::vec2(size);
}

void SpriteAtlas::Destroy() {
    Texture::Destroy();
}

glm::vec2 SpriteAtlas::SpriteUV(glm::vec2 sprite_coordinates) {
    return glm::vec2(
        sprite_coordinates.x * sprite_unit.x,
        sprite_coordinates.y * sprite_unit.y
    );
}
