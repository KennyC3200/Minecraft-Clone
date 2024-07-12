#include "game.hpp"

Game::Game() {}

Game::~Game() {}

void Game::init() {
    window.init();
    renderer.init();
    world.init();

    loop();
}

void Game::destroy() {
    world.destroy();
    renderer.destroy();
    window.destroy();
}

void Game::loop() {
    while (!glfwWindowShouldClose(window.handle)) {
        glfwPollEvents();

        glClearColor(0.580f, 0.800f, 0.976f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glfwSwapBuffers(window.handle);
    }
}
