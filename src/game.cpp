#include "game.hpp"

Game::Game() {}

Game::~Game() {}

void Game::init() {
    // Gfx
    window.init();
    world.init();
    renderer.init(&world);

    // Inputs
    keyboard.init(&window);
    mouse.init(&window, true);

    // Player
    player.init(&window, &keyboard, &mouse);
}

void Game::destroy() {
    // Gfx
    window.destroy();
    world.destroy();
    renderer.destroy();
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
    // Input
    keyboard.update();
    mouse.update();

    // Player
    player.update();
}

void Game::render() {
    renderer.render();
}
