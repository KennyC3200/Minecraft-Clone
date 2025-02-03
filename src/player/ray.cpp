#include "ray.h"

namespace mc {

RaycastData Raycast(World* world, glm::vec3 position, glm::vec3 direction, float max_distance) {
    glm::ivec3 step;
    glm::vec3 d_length, d_delta;
    glm::ivec3 iter_pos, out;
    float radius;

    iter_pos = glm::ivec3(floor(position.x), floor(position.y), floor(position.z));
    step = {SIGN(direction.x), SIGN(direction.y), SIGN(direction.z)};

    d_length = intbound(position, direction);
    d_delta = glm::vec3(step) / direction;

    radius = max_distance / glm::length(direction);

    while (true) {
        if (d_length.x < d_length.y) {
            if (d_length.x < d_length.z) {
                if (d_length.x > radius) {
                    break;
                }

                iter_pos.x += step.x;
                d_length.x += d_delta.x;
                out = {-step.x, 0, 0};
            } else {
                if (d_length.z > radius) {
                    break;
                }

                iter_pos.z += step.z;
                d_length.z += d_delta.z;
                out = {0, 0, -step.z};
            }
        } else {
            if (d_length.y < d_length.z) {
                if (d_length.y > radius) {
                    break;
                }

                iter_pos.y += step.y;
                d_length.y += d_delta.y;
                out = {0, -step.y, 0};
            } else {
                if (d_length.z > radius) {
                    break;
                }

                iter_pos.z += step.z;
                d_length.z += d_delta.z;
                out = {0, 0, -step.z};
            }
        }

        Block* block = world->GetBlock(iter_pos);
        if (block == nullptr) {
            continue;
        }
        if (block->GetID() != BLOCK_AIR) {
            return (RaycastData) {
                .hit = true,
                .position = iter_pos,
                .out = out
            };
        }
    }
    return (RaycastData) {
        .hit = false,
        .position = iter_pos,
        .out = out
    };
}

}
