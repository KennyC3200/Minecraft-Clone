#include "ui.hpp"

void UI::init(Window *window, Renderer *renderer, World *world, Player *player) {
    this->window = window;
    this->renderer = renderer;
    this->world = world;
    this->player = player;

    UIComponent::init(this->window);
    crosshair.init();
    hotbar.init();

    init_imgui(window->handle);

    toggled = true;
    overview.toggled = true;
    camera.toggled = true;
    settings.toggled = false;
    settings.demo_window = false;

    reset_button_id = 0;
}

void UI::destroy() {
    UIComponent::destroy();
    crosshair.destroy();
    hotbar.destroy();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UI::render() {
    render_components();

    if (!toggled) {
        return;
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (overview.toggled) {
        render_overview();
    }
    if (camera.toggled) {
        render_camera();
    }
    if (settings.toggled) {
        render_settings();
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

void UI::render_components() {
    UIComponent::shader.bind();

    crosshair.render();
    hotbar.render();
}

void UI::render_overview() {
    ImGui::Begin("Overview");
    ImGui::Text("FPS: %i", (int) window->fps);
    ImGui::SeparatorText("Game");
    ImGui::Text("Position: %i %i %i", (int) player->game_data.position.x, (int) player->game_data.position.y, (int) player->game_data.position.z);
    ImGui::Text("Chunk Position: %.2f %.2f %.2f", player->game_data.chunk_position.x, player->game_data.chunk_position.y, player->game_data.chunk_position.z);
    ImGui::SeparatorText("World");
    ImGui::Text("Position: %i %i %i", (int) player->world_data.position.x, (int) player->world_data.position.y, (int) player->world_data.position.z);
    ImGui::Text("Chunk Position: %.2f %.2f %.2f", player->world_data.chunk_position.x, player->world_data.chunk_position.y, player->world_data.chunk_position.z);
    ImGui::SeparatorText("Chunk");
    ImGui::Text("Position: %i %i %i", (int) player->chunk_data.position.x, (int) player->chunk_data.position.y, (int) player->chunk_data.position.z);
    ImGui::End();
}

void UI::render_camera() {
    ImGui::Begin("Camera");
    ImGui::SeparatorText("Overview");
    ImGui::Text("Pitch: %.2f", player->camera.pitch);
    ImGui::Text("Yaw: %.2f", player->camera.yaw);
    ImGui::SeparatorText("Ray");
    ImGui::Text("Hit: %lu %lu %lu", player->ray.tmp.position.x, player->ray.tmp.position.y, player->ray.tmp.position.z);
    // ImGui::SliderFloat("FOV", &player->camera.fov, 1.0f, 80.0f);
    // UI_RESET_BUTTON(1, player->camera.fov = 45.0f;);
    // ImGui::SliderFloat("Z-far", &player->camera.z_far, 1.0f, 500.0f);
    // UI_RESET_BUTTON(2, player->camera.z_far = 1000.0f;);
    // ImGui::SliderFloat("Sensitivity", &player->camera.sensitivity, 0.0f, 1.0f);
    // UI_RESET_BUTTON(3, player->camera.sensitivity = 0.1f;);
    ImGui::End();
}

void UI::render_settings() {
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
