#include "ui.hpp"

void UI::init(Window *window, Renderer *renderer, World *world, Player *player) {
    this->window = window;
    this->renderer = renderer;
    this->world = world;
    this->player = player;

    init_imgui(window->handle);

    toggled = true;
    overview.toggled = true;
    command_tools.toggled = false;

    reset_button_id = 0;
}

void UI::destroy() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UI::render() {
    if (!toggled) {
        return;
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (overview.toggled) {
        render_overview();
    }
    if (command_tools.toggled) {
        render_command_tools();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::init_imgui(GLFWwindow *window) {
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

void UI::render_overview() {
    ImGui::Begin("Overview");
    ImGui::Text("FPS: %i", (int) window->fps);
    ImGui::End();
}

void UI::render_command_tools() {
    ImGui::Begin("Command Tools");

    ImGui::SeparatorText("Camera");
    ImGui::SliderFloat("FOV", &player->camera.fov, 1.0f, 80.0f);
    UI_RESET_BUTTON(1, player->camera.fov = 45.0f;);
    ImGui::SliderFloat("Z-far", &player->camera.z_far, 1.0f, 300.0f);
    UI_RESET_BUTTON(2, player->camera.z_far = 200.0f;);
    ImGui::SliderFloat("Sensitivity", &player->camera.sensitivity, 0.0f, 1.0f);
    UI_RESET_BUTTON(3, player->camera.sensitivity = 0.1f;);

    ImGui::SeparatorText("Settings");
    ImGui::Text("Window Size: %i %i", window->size.x, window->size.y);
    ImGui::Checkbox("Overview", &overview.toggled);
    ImGui::Checkbox("Wireframe (t)", &renderer->flags.wireframe);
    if (command_tools.demo_window) {
        ImGui::ShowDemoWindow(&command_tools.demo_window);
    }
    ImGui::Checkbox("Demo Window", &command_tools.demo_window);

    ImGui::End();
}
