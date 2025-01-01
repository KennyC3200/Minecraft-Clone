#pragma once

#include "../util/util.h"
#include "../gfx/window.h"
#include "../input/keyboard.h"
#include "../input/mouse.h"
#include "../world/world.h"
#include "camera.h"
#include "ray.h"

class Player {
public:
    void Init(Window* window, Keyboard* keyboard, Mouse* mouse, World* world);
    void Update();

    Camera& GetCamera();

    glm::vec3 offset, position;
    glm::ivec3 chunk_position;

    // TODO: Make this an enum so that you pass in
    //       This makes it so that the idx cannot go out of bounds :)
    // void set_hotbar_idx(enum HotbarIndex idx)
    static constexpr int hotbar_size = 9;
    BlockID hotbar[hotbar_size];
    int current_hotbar_idx;

private:
    Window* window;
    Keyboard* keyboard;
    Mouse* mouse;
    World* world;

    float speed;
    Camera camera;
    Ray ray;
};
