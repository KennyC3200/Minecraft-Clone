#include "game.h"

void Game::Init() {
    window.Init();
    world.Init();
    renderer.Init(&world, &player);
    ui.Init(&window, &renderer, &world, &player);

    keyboard.Init(&window);
    mouse.Init(&window);

    player.Init(&window, &keyboard, &mouse, &world);
}

void Game::Destroy() {
    ui.Destroy();
    window.Destroy();
    world.Destroy();
}

void Game::Loop() {
    while (!glfwWindowShouldClose(window.handle)) {
        glfwPollEvents();

        glClearColor(0.580f, 0.800f, 0.976f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Update();
        Render();

        glfwSwapBuffers(window.handle);
    }
}

void Game::Update() {
    window.Update();

    keyboard.Update();
    mouse.Update();

    player.Update();

    if (keyboard.GetButton(GLFW_KEY_T).pressed) {
        renderer.flags.wireframe = !renderer.flags.wireframe;
    }
    if (keyboard.GetButton(GLFW_KEY_ESCAPE).pressed) {
        ui.settings.toggled = !ui.settings.toggled;
        mouse.SetToggled(ui.settings.toggled);
        player.GetCamera().SetToggled(!ui.settings.toggled);
    }
}

void Game::Render() {
    renderer.Render();
    ui.Render();
}
