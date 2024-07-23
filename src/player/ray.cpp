#include "ray.hpp"

void Ray::init(float max_distance, glm::vec<3, size_t> data_size) {
    this->max_distance = max_distance;
    this->data_size = data_size;
}

void Ray::update(uint64_t *data, glm::vec3 position, glm::vec3 direction) {
    this->data = data;
    this->position = position;
    this->direction = direction;
}

RayCastData Ray::cast() {
    glm::vec3 step;
    glm::vec3 d_length, d_delta;
    glm::ivec3 _position;

    _position = glm::ivec3(position);
    step = {SIGN(direction.x), SIGN(direction.y), SIGN(direction.z)};

    d_length = intbound(position, direction);
    d_delta = step / direction;

    while (true) {
        if (d_length.x < d_length.y) {
            if (d_length.x < d_length.z) {
                _position.x += step.x;
                d_length.x += d_delta.x;
            } else {
                _position.z += step.z;
                d_length.z += d_delta.z;
            }
        } else {
            if (d_length.y < d_length.z) {
                _position.y += step.y;
                d_length.y += d_delta.y;
            } else {
                _position.z += step.z;
                d_length.z += d_delta.z;
            }
        }

        // TODO: its gonna seg fault if the player is looking at somewhere not in the chunk
        // TODO: what if the player wants to delete blocks in other chunks? Currently would only work if the player is deleting the block in the chunk the player is standing in
        // TODO: this only works with having z has the second parameter: (x, z, y) instead of (x, y, z)
        if (data[_position.x * data_size.y * data_size.z + _position.z * data_size.y + _position.y]) {
            break;
        }
    }

    RayCastData data;
    data.hit = true;
    data.position = _position;

    tmp = data;

    return data;
}
