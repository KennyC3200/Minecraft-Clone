#pragma once

#include "gfx.h"
#include "texture.h"

class SpriteAtlas {
public:
    SpriteAtlas();
    ~SpriteAtlas();
    SpriteAtlas(std::string path, std::string fs_name, glm::vec2 sprite_size);

    glm::vec2 sprite_uv(glm::vec2 sprite_coordinates);

    Texture texture;
    glm::vec2 size, sprite_size;
    glm::vec2 sprite_unit, pixel_unit;
};
