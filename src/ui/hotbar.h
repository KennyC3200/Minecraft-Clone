#pragma once

#include "ui_component.h"
#include "../gfx/sprite_atlas.h"
#include "../player/player.h"

class Hotbar : public UIComponent {
public:
    void Init(Player* player);
    void Destroy();
    void Mesh();
    void Render();

private:
    void RenderHotbar(glm::vec2 p1, glm::vec2 p2, bool toggled);
    void RenderItems(glm::vec2 p1, glm::vec2 p2, BlockID block);

    Player* player;
    SpriteAtlas atlas;
};
