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
    Player *player;
    SpriteAtlas atlas;
};
