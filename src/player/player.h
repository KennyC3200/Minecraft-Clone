#pragma once

#include "../util/util.h"
#include "../gfx/window.h"
#include "../input/keyboard.h"
#include "../input/mouse.h"
#include "../world/world.h"
#include "camera.h"
#include "ray.h"

class HudManager;

class Player {
public:
    void Init(Window* window, Keyboard* keyboard, Mouse* mouse, World* world);
    void Update();

    Camera& GetCamera();
    BlockID GetHotbarItem(int idx);
    int GetCurrentHotbarIdx();

    static constexpr int hotbar_size = 9;

private:
    Window* window;
    Keyboard* keyboard;
    Mouse* mouse;
    World* world;

    glm::vec3 offset, position;

    float speed;
    Camera camera;

    BlockID hotbar[hotbar_size];
    int current_hotbar_idx;
};
