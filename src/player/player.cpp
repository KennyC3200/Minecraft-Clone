#include "player.hpp"

void Player::init(Window *window, Keyboard *keyboard, Mouse *mouse, World *world) {
    this->window = window;
    this->keyboard = keyboard;
    this->mouse = mouse;
    this->world = world;

    speed = 30.0f;

    offset = {CHUNK_SIZE_X * world->chunks_size.x / 2, CHUNK_SIZE_Y, CHUNK_SIZE_Z * world->chunks_size.z / 2};
    position = {0, 0, 0};

    camera.init(window, mouse, offset);
    ray.init(this->world, 8.0f);
}

void Player::update() {
    glm::vec3 displacement;
    float _displacement;
    if (keyboard->keys[GLFW_KEY_W].down) {
        displacement = speed * (float) window->time_delta * camera.direction;
        camera.position += displacement;
        position += displacement;
    }
    if (keyboard->keys[GLFW_KEY_S].down) {
        displacement = speed * (float) window->time_delta * camera.direction;
        camera.position -= displacement;
        position -= displacement;
    }
    if (keyboard->keys[GLFW_KEY_A].down) {
        displacement = speed * (float) window->time_delta * camera.right;
        camera.position -= displacement;
        position -= displacement;
    }
    if (keyboard->keys[GLFW_KEY_D].down) {
        displacement = speed * (float) window->time_delta * camera.right;
        camera.position += displacement;
        position += displacement;
    }
    if (keyboard->keys[GLFW_KEY_SPACE].down) {
        _displacement = speed * (float) window->time_delta;
        camera.position.y += _displacement;
        position.y += _displacement;
    }
    if (keyboard->keys[GLFW_KEY_LEFT_SHIFT].down) {
        _displacement = speed * (float) window->time_delta; 
        camera.position.y -= _displacement;
        position.y -= _displacement;
    }
    if (mouse->keys[GLFW_MOUSE_BUTTON_LEFT].pressed) {
        RayCastData raycast = ray.cast(position + offset, camera.front);
        if (raycast.hit) {
            BlockData *block = world->block_get(raycast.position);
            *block = BLOCK_AIR;
            Chunk *chunk = world->chunk_get(raycast.position);
            chunk->meshed = false;
        }
    }

    camera.update();
    // TODO: need to refactor between camera.front and camera.direction
    // ray.update(world->chunks[idx]->data, chunk_data.game_position, camera.front);
}

void Player::render() {
    ChunkMesh::shader.uniform_mat4("view", camera.view);
    ChunkMesh::shader.uniform_mat4("projection", camera.projection);
}
