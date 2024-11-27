#include "ray.hpp"

void Ray::init(World *world, float max_distance) {
    this->world = world;
    this->max_distance = max_distance;
}

RayCastData Ray::cast(glm::vec3 position, glm::vec3 direction) {
    glm::vec3 step;
    glm::vec3 d_length, d_delta;
    glm::ivec3 _position, _out;
    float radius;

    _position = glm::ivec3(floor(position.x), floor(position.y), floor(position.z));
    step = {SIGN(direction.x), SIGN(direction.y), SIGN(direction.z)};

    d_length = intbound(position, direction);
    d_delta = step / direction;

    radius = max_distance / glm::length(direction);

    while (true) {
        if (d_length.x < d_length.y) {
            if (d_length.x < d_length.z) {
                if (d_length.x > radius) {
                    break;
                }

                _position.x += step.x;
                d_length.x += d_delta.x;
                _out = {-step.x, 0, 0};
            } else {
                if (d_length.z > radius) {
                    break;
                }

                _position.z += step.z;
                d_length.z += d_delta.z;
                _out = {0, 0, -step.z};
            }
        } else {
            if (d_length.y < d_length.z) {
                if (d_length.y > radius) {
                    break;
                }

                _position.y += step.y;
                d_length.y += d_delta.y;
                _out = {0, -step.y, 0};
            } else {
                if (d_length.z > radius) {
                    break;
                }

                _position.z += step.z;
                d_length.z += d_delta.z;
                _out = {0, 0, -step.z};
            }
        }

        Block *block = world->block_get(_position);
        if (block == nullptr) {
            continue;
        }
        if (block->get_id() != BLOCK_AIR) {
            return (RayCastData) {
                .hit = true,
                .position = _position,
                .out = _out
            };
        }
    }
    return (RayCastData) {
        .hit = false,
        .position = _position,
        .out = {0, 0, 0}
    };
}
