#include "sprite_atlas.h"

SpriteAtlas::SpriteAtlas() {}

SpriteAtlas::~SpriteAtlas() {}

SpriteAtlas::SpriteAtlas(std::string path, std::string fs_name, glm::vec2 sprite_size)
    : sprite_size(sprite_size)
{
    texture.init(path, fs_name, GL_RGBA, GL_RGBA);
    size = texture.size;
    sprite_unit = sprite_size / size;
    pixel_unit = 1.0f / size;
}

glm::vec2 SpriteAtlas::sprite_uv(glm::vec2 sprite_coordinates) {
    return glm::vec2(
        sprite_coordinates.x * sprite_unit.x,
        sprite_coordinates.y * sprite_unit.y
    );
}
