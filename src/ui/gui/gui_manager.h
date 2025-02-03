#pragma once

#define GLFW_INCLUDE_NONE
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

#include "../../gfx/window.h"
#include "../../player/player.h"
#include "../../world/world.h"

class GuiManager {
public:
    void Init(Window* window, World* world, Player* player);
    void Destroy();
    void Render();

private:
    Window* window;
    World* world;
    Player* player;

    ImGuiIO* io;
};
