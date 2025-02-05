#pragma once

#include "../gfx/window.h"
#include "../input/keyboard.h"
#include "../input/mouse.h"
#include "../world/world.h"
#include "camera.h"

class HudManager;

class Player {
public:
    void Init(Window* window, Keyboard* keyboard, Mouse* mouse, World* world);
    void Update();

    inline glm::vec3 GetPosition() { return position; }
    inline glm::ivec3 GetChunkPosition() { return chunk_position; }
    inline Camera& GetCamera() { return camera; }
    BlockID GetHotbarItem(int idx);
    int GetHotbarIdx();

    static constexpr int hotbar_size = 9;

private:
    Window* window;
    Keyboard* keyboard;
    Mouse* mouse;
    World* world;

    glm::vec3 offset, position;
    glm::ivec3 chunk_position, chunk_position_prev;

    float height;
    float speed;
    Camera camera;

    BlockID hotbar[hotbar_size];
    int hotbar_idx;
};
