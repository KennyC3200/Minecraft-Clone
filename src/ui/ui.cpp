#include "ui.h"

void UI::Init(Window* window, Renderer* renderer, World* world, Player* player) {
    this->window = window;
    this->renderer = renderer;
    this->world = world;
    this->player = player;

    UIComponent::Init(this->window);
    crosshair.Init();
    hotbar.Init(this->player);

    InitImgui(window->handle);

    toggled = true;
    overview.toggled = true;
    settings.toggled = false;
    settings.demo_window = false;

    reset_button_id = 0;
}

void UI::Destroy() {
    UIComponent::Destroy();
    crosshair.Destroy();
    hotbar.Destroy();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UI::Render() {
    RenderComponents();

    if (!toggled) {
        return;
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (overview.toggled) {
        RenderOverview();
    }
    if (settings.toggled) {
        RenderSettings();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::InitImgui(GLFWwindow *window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO(); (void)io;

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char *glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char *glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char *glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    ImGui::StyleColorsDark();
}

void UI::RenderComponents() {
    UIComponent::shader.Bind();
    crosshair.Render();
    hotbar.Render();
}

void UI::RenderOverview() {
    ImGui::Begin("Overview");
    UI_INT(FPS, (int) window->fps);
    UI_VEC3(Position, player->position);
    UI_VEC3(Position + Offset, player->position + player->offset);
    ImGui::End();
}

void UI::RenderSettings() {
    ImGui::Begin("Settings");
    ImGui::Text("Window Size: %ipx %ipx", window->size.x, window->size.y);
    ImGui::Checkbox("Overview", &overview.toggled);
    ImGui::Checkbox("Wireframe (t)", &renderer->flags.wireframe);
    if (settings.demo_window) {
        ImGui::ShowDemoWindow(&settings.demo_window);
    }
    ImGui::Checkbox("Demo Window", &settings.demo_window);
    ImGui::End();
}
