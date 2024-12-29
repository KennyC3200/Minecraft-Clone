#pragma once

#include "ui_component.h"
#include "../gfx/sprite_atlas.h"
#include "../player/player.h"

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
