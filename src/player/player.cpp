#include "player.h"

void Player::init(Window *window, Keyboard *keyboard, Mouse *mouse, World *world) {
    this->window = window;
    this->keyboard = keyboard;
    this->mouse = mouse;
    this->world = world;

    speed = 15.0f;

    std::fill(hotbar, hotbar + Player::HOTBAR_SIZE, BLOCK_NONE);
    hotbar[0] = BLOCK_DIRT;
    hotbar[1] = BLOCK_GRASS;
    hotbar[2] = BLOCK_STONE;
    hotbar[3] = BLOCK_SAND;
    hotbar[4] = BLOCK_LOG;
    hotbar[5] = BLOCK_PLANK;
    current_hotbar_idx = 0;

    float player_height = 1.8f;
    offset = {
        ChunkMesh::CHUNK_SIZE.x * world->chunks_size.x / 2, 
        ChunkMesh::CHUNK_SIZE.y * world->ground_level + player_height, 
        ChunkMesh::CHUNK_SIZE.z * world->chunks_size.z / 2
    };
    offset += 0.0001;
    position = offset;

    camera.init(window, mouse, offset);
    ray.init(this->world, 8.0f);
}

/* Update the player 
 * Handle movement
 * Update camera
 * Handle block placement/deletion
 * */
void Player::update() {
    float displacement = speed * window->time_delta;
    if (keyboard->get_button(GLFW_KEY_W).down) {
        position += displacement * camera.get_front();
    }
    if (keyboard->get_button(GLFW_KEY_S).down) {
        position -= displacement * camera.get_front();
    }
    if (keyboard->get_button(GLFW_KEY_A).down) {
        position -= displacement * camera.get_right();
    }
    if (keyboard->get_button(GLFW_KEY_D).down) {
        position += displacement * camera.get_right();
    }
    if (keyboard->get_button(GLFW_KEY_SPACE).down) {
        position.y += 0.5f * displacement;
    }
    if (keyboard->get_button(GLFW_KEY_LEFT_SHIFT).down) {
        position.y -= 0.5f * displacement;
    }

    // Update the camera
    camera.position = position;
    camera.update();

    /* Handle the hotbar
     * Keep in mind the index starts at 0, not 1
     * */
    for (int i = 0; i < Player::HOTBAR_SIZE; i++) {
        if (keyboard->get_button(GLFW_KEY_1 + i).pressed) {
            current_hotbar_idx = i;
        }
    }

    // Handle block placement/deletion
    RayCastData raycast = ray.cast(position, camera.direction);
    if (raycast.hit) {
        if (mouse->get_button(GLFW_MOUSE_BUTTON_LEFT).pressed) {
            world->get_block(raycast.position)->set_id(BLOCK_AIR);
            world->get_chunk(raycast.position)->set_dirty();
        }
        if (mouse->get_button(GLFW_MOUSE_BUTTON_RIGHT).pressed) {
            glm::vec3 block_position = raycast.position + raycast.out;
            Block *block = world->get_block(block_position);

            if (block != nullptr && block->get_id() == BLOCK_AIR) {
                world->get_block(block_position)->set_id(hotbar[current_hotbar_idx]);
                world->get_chunk(block_position)->set_dirty();
            }
        }
    }
}

void Player::render() {
    ChunkMesh::shader.uniform_mat4("view", camera.view);
    ChunkMesh::shader.uniform_mat4("projection", camera.projection);
}

Camera &Player::get_camera() {
    return camera;
}
