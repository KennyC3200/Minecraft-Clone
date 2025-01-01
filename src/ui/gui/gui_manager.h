#pragma once

#define GLFW_INCLUDE_NONE
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

#include "../../gfx/window.h"
#include "../../player/player.h"

class GuiManager {
public:
    void Init(Window* window, Player* player);
    void Destroy();
    void Render();

private:
    Window* window;
    Player* player;

    ImGuiIO* io;
};
