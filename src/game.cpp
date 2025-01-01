#include "game.h"

void Game::Init() {
    window.Init({1440, 900});
    world.Init();

    keyboard.Init(&window);
    mouse.Init(&window);

    player.Init(&window, &keyboard, &mouse, &world);

    hud_manager.Init(&window, &player);
    gui_manager.Init(&window, &player);

    renderer.Init(&world, &player, &hud_manager, &gui_manager);
}

void Game::Destroy() {
    hud_manager.Destroy();
    gui_manager.Destroy();
    world.Destroy();
    window.Destroy();
}

void Game::Loop() {
    while (!glfwWindowShouldClose(window.GetHandle())) {
        glfwPollEvents();

        glClearColor(0.580f, 0.800f, 0.976f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Update();
        Render();

        glfwSwapBuffers(window.GetHandle());
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
        mouse.SetToggled(!mouse.GetToggled());
        player.GetCamera().SetToggled(!mouse.GetToggled());
    }
}

void Game::Render() {
    renderer.Render();
}
