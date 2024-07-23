#include "ray.hpp"

void Ray::init(uint64_t **data, float max_distance) {
    this->data = data;
    this->max_distance = max_distance;
}

void Ray::update(glm::vec3 position, glm::vec3 direction) {
    this->position = position;
    this->direction = direction;
}

RayCastData Ray::cast() {
    glm::vec3 step;
    glm::vec3 d_length, d_delta;
    glm::vec<3, int> _position;

    _position = {(int) position.x, (int) position.y, (int) position.z};
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
        break;
    }

    RayCastData data;
    data.hit = true;
    data.position = _position;

    return data;
}
