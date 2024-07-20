#pragma once

#define GLFW_INCLUDE_NONE
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

#include "crosshair.hpp"
#include "hotbar.hpp"
#include "../util/util.hpp"
#include "../gfx/window.hpp"
#include "../gfx/renderer.hpp"
#include "../world/world.hpp"
#include "../player/player.hpp"

#define UI_RESET_BUTTON(id, assignment)\
ImGui::SameLine();\
if (ImGui::Button("Reset##"#id))\
    assignment

class UI {
public:
    void init(Window *window, Renderer *renderer, World *world, Player *player);
    void destroy();
    void render();

    Crosshair crosshair;
    Hotbar hotbar;

    bool toggled;
    struct {
        bool toggled;
    } overview;
    struct {
        bool toggled;
        bool demo_window;
    } command_tools;
private:
    void init_imgui(GLFWwindow *window);
    void render_components();
    void render_overview();
    void render_command_tools();

    ImGuiIO *io;
    int reset_button_id;

    Window *window;
    Renderer *renderer;
    World *world;
    Player *player;
};
