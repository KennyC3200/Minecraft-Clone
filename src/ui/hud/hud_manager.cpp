#include "hud_manager.h"

Crosshair HudManager::crosshair;
Hotbar HudManager::hotbar;

void HudManager::Init(Window* window, Player* player) {
    HudComponent::Init(window);

    crosshair.Init();
    hotbar.Init(player);
}

void HudManager::Destroy() {
    HudComponent::Destroy();
}

void HudManager::Render() {
    HudComponent::shader.Bind();

    if (!crosshair.meshed) {
        crosshair.Mesh();
        crosshair.meshed = true;
    }
    crosshair.Render();

    if (!hotbar.meshed) {
        hotbar.Mesh();
        hotbar.meshed = true;
    }
    hotbar.Render();
}

void HudManager::MeshCrosshair() {
    crosshair.meshed = false;
}

void HudManager::MeshHotbar() {
    hotbar.meshed = false;
}
