#include "player.hpp"

void Player::init(Window *window, Keyboard *keyboard, Mouse *mouse, World *world) {
    this->window = window;
    this->keyboard = keyboard;
    this->mouse = mouse;
    this->world = world;

    speed = 30.0f;

    camera.init(window, mouse);
    ray.init(5.0f, {CHUNK_SIZE_X, CHUNK_SIZE_Y, CHUNK_SIZE_Z});

    world_data.chunk_position = world->chunks_center;
}

void Player::update() {
    if (keyboard->keys[GLFW_KEY_W].down) {
        camera.position += speed * (float) window->time_delta * camera.direction;
    }
    if (keyboard->keys[GLFW_KEY_S].down) {
        camera.position -= speed * (float) window->time_delta * camera.direction;
    }
    if (keyboard->keys[GLFW_KEY_A].down) {
        camera.position -= speed * (float) window->time_delta * camera.right;
    }
    if (keyboard->keys[GLFW_KEY_D].down) {
        camera.position += speed * (float) window->time_delta * camera.right;
    }
    if (keyboard->keys[GLFW_KEY_SPACE].down) {
        camera.position.y += speed * (float) window->time_delta;
    }
    if (keyboard->keys[GLFW_KEY_LEFT_SHIFT].down) {
        camera.position.y -= speed * (float) window->time_delta;
    }

    size_t idx = world->chunks_idx((int) game_data.chunk_position.x, (int) game_data.chunk_position.y, (int) game_data.chunk_position.z);
    if (mouse->keys[GLFW_MOUSE_BUTTON_LEFT].pressed) {
        if (world->chunks[idx]->data[CHUNK_POS_TO_IDX(8, 15, 8)] == BLOCK_AIR) {
            world->chunks[idx]->data[CHUNK_POS_TO_IDX(8, 15, 8)] = BLOCK_GRASS;
        } else {
            world->chunks[idx]->data[CHUNK_POS_TO_IDX(8, 15, 8)] = BLOCK_AIR;
        }
        world->chunks[idx]->meshed = false;
    }

    camera.update();
    // TODO: need to refactor between camera.front and camera.direction
    ray.update(world->chunks[idx]->data, chunk_data.game_position, camera.front);
    ray.cast();

    game_data.position = {camera.position.x, camera.position.y, camera.position.z};
    game_data.chunk_position = world->chunks_center + game_data.position / 16.0f;

    world_data.position = {game_data.position.x, game_data.position.y, -game_data.position.z};
    world_data.chunk_position = world_data.position / 16.0f;

    chunk_data.game_position = 16.0f * (game_data.chunk_position - glm::vec3(glm::ivec3(game_data.chunk_position))) + glm::vec3(0.0f, CHUNK_SIZE_Y - 1, 0.0f);
    chunk_data.world_position = 16.0f * (world_data.chunk_position - glm::vec3(glm::ivec3(world_data.chunk_position))) + glm::vec3(0.0f, CHUNK_SIZE_Y - 1, 0.0f);
}

void Player::render() {
    ChunkMesh::shader.uniform_mat4("view", camera.view);
    ChunkMesh::shader.uniform_mat4("projection", camera.projection);
}
