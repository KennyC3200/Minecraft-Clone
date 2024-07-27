#include "hotbar.hpp"

void Hotbar::init(Player *player) {
    this->player = player;

    toggled = true;
    atlas = SpriteAtlas("res/images/hotbar.png", "tex", {22, 22});
}

void Hotbar::render() {
    if (!toggled) {
        return;
    }

    UIComponent::shader.uniform_texture_2d(atlas.texture, 0);
    for (int i = 0; i < HOTBAR_SIZE; i++) {
        // have vertices and indices
        // buffer the uv coordinates separately
        if (i == player->hotbar_idx) {
        } else {
        }
    }
}
