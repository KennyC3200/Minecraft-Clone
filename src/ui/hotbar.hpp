#pragma once

#include "ui_component.hpp"
#include "../gfx/sprite_atlas.hpp"
#include "../player/player.hpp"

class Hotbar : public UIComponent {
public:
    void init(Player *player);
    void mesh();
    void render();
private:
    void render_hotbar(glm::vec2 p1, glm::vec2 p2, bool toggled);
    void render_items(glm::vec2 p1, glm::vec2 p2, BlockID block);

    Player *player;
    SpriteAtlas atlas;
};
