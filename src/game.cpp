#include "game.h"

void Game::init() {
    window.init();
    world.init();
    renderer.init(&world, &player);
    ui.init(&window, &renderer, &world, &player);

    keyboard.init(&window);
    mouse.init(&window);

    player.init(&window, &keyboard, &mouse, &world);
}

void Game::destroy() {
    ui.destroy();
    window.destroy();
    world.destroy();
}

void Game::loop() {
    while (!glfwWindowShouldClose(window.handle)) {
        glfwPollEvents();

        glClearColor(0.580f, 0.800f, 0.976f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        update();
        render();

        glfwSwapBuffers(window.handle);
    }
}

void Game::update() {
    window.update();

    keyboard.update();
    mouse.update();

    player.update();

    if (keyboard.get_button(GLFW_KEY_T).pressed) {
        renderer.flags.wireframe = !renderer.flags.wireframe;
    }
    if (keyboard.get_button(GLFW_KEY_ESCAPE).pressed) {
        ui.settings.toggled = !ui.settings.toggled;
        mouse.set_toggled(ui.settings.toggled);
        player.get_camera().set_toggled(!ui.settings.toggled);
    }
}

void Game::render() {
    renderer.render();
    ui.render();
}
