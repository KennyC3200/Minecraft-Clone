#pragma once

#include "texture.h"

class SpriteAtlas : public Texture {
public:
    SpriteAtlas() = default;

    void Init(const std::string& path, const std::string& fs_name, glm::vec2 sprite_size);
    void Destroy();

    glm::vec2 SpriteUV(int x, int y);
    glm::vec2 SpriteUV(glm::ivec2 sprite_coordinates);
    glm::ivec2 SpritesSize();

private:
    glm::vec2 sprite_size;
    glm::vec2 sprite_unit, pixel_unit;
    glm::ivec2 sprites_size;
};
