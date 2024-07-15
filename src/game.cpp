#include "game.hpp"

void Game::init() {
    // gfx 
    window.init();
    world.init(&player);
    renderer.init(&world, &player);
    ui.init(&window, &renderer, &world, &player);

    // inputs
    keyboard.init(&window);
    mouse.init(&window);

    // player
    player.init(&window, &keyboard, &mouse);
}

void Game::destroy() {
    // gfx
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
    // gfx
    window.update();

    // input
    keyboard.update();
    mouse.update();

    // player
    player.update();

    if (keyboard.keys[GLFW_KEY_T].pressed) {
        renderer.flags.wireframe = !renderer.flags.wireframe;
    }
    if (keyboard.keys[GLFW_KEY_ESCAPE].pressed) {
        ui.command_tools.toggled = !ui.command_tools.toggled;
        mouse.toggled = ui.command_tools.toggled;
        player.camera.toggled = !ui.command_tools.toggled;
    }
}

void Game::render() {
    renderer.render();
    ui.render();
}
