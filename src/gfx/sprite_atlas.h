#pragma once

#include "gfx.h"
#include "texture.h"

class SpriteAtlas : public Texture {
public:
    SpriteAtlas() = default;

    void Init(const std::string& path, const std::string& fs_name, glm::vec2 sprite_size);
    void Destroy();

    glm::vec2 SpriteUV(glm::vec2 sprite_coordinates);

private:
    glm::vec2 sprite_size;
    glm::vec2 sprite_unit, pixel_unit;
};
