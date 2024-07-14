#include "sprite_atlas.hpp"

SpriteAtlas::SpriteAtlas() {}

SpriteAtlas::~SpriteAtlas() {}

SpriteAtlas::SpriteAtlas(std::string path, std::string fs_name, glm::vec2 sprite_size):
sprite_size(sprite_size)
{
    texture.init(path, fs_name, GL_RGBA, GL_RGBA);
    size = texture.size;
    sprite_unit = sprite_size / size;
    pixel_unit = 1.0f / size;

#ifdef SPRITEATLAS_DEBUG
    std::cout << "TextureAtlas: " << path << " (" << fs_name << ")" << '\n'
        << "size: " << size.x << ' ' << size.y << '\n'
        << "sprite_unit: " << sprite_unit.x << ' ' << sprite_unit.y << '\n'
        << "pixel_unit: " << pixel_unit.x << ' ' << pixel_unit.y << '\n';
#endif
}

glm::vec2 SpriteAtlas::sprite_uv(glm::vec2 sprite_coordinates) {
    return glm::vec2(
        sprite_coordinates.x * sprite_unit.x,
        sprite_coordinates.y * sprite_unit.y
    );
}
