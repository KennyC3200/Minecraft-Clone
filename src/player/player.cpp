#include "player.hpp"

void Player::init(Window *window, Keyboard *keyboard, Mouse *mouse, World *world) {
    this->window = window;
    this->keyboard = keyboard;
    this->mouse = mouse;
    this->world = world;

    camera.init(window, mouse);
}

void Player::update() {
    // handle movement
    if (keyboard->keys[GLFW_KEY_W].down) {
        camera.position += 60.0f * (float) window->time_delta * camera.front;
    }
    if (keyboard->keys[GLFW_KEY_S].down) {
        camera.position -= 60.0f * (float) window->time_delta * camera.front;
    }
    if (keyboard->keys[GLFW_KEY_A].down) {
        camera.position -= 60.0f * (float) window->time_delta * glm::normalize(glm::cross(camera.front, camera.up));
    }
    if (keyboard->keys[GLFW_KEY_D].down) {
        camera.position += 60.0f * (float) window->time_delta * glm::normalize(glm::cross(camera.front, camera.up));
    }
    if (keyboard->keys[GLFW_KEY_0].pressed) {
        for (int x = 0; x < 10; x++) {
            for (int y = 0; y < 12; y++) {
                for (int z = 0; z < 10; z++) {
                    world->chunks[world->chunks_idx(5, 1, 5)]->data[CHUNK_POS_TO_IDX(x + 2, 15 - y, z + 2)] = BLOCK_AIR;
                }
            }
        }
        world->chunks[world->chunks_idx(5, 1, 5)]->meshed = false;
    }
    camera.update();

    position = camera.position;

    // handle ray casting
}

void Player::render() {
    // TODO: implement third-person
    ChunkMesh::shader.uniform_mat4("view", camera.view);
    ChunkMesh::shader.uniform_mat4("projection", camera.projection);
}
