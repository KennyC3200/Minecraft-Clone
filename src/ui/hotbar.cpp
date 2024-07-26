#include "hotbar.hpp"

void Hotbar::init() {
    toggled = true;
    atlas = SpriteAtlas("res/images/hotbar.png", "tex", {22, 22});
}

void Hotbar::render() {
    if (!toggled) {
        return;
    }
}
