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
    RayCastData data;

    glm::vec3 step, d_delta;
    glm::vec<3, int> _position;
    float d_max;

    _position = {(int) position.x, (int) position.y, (int) position.z};
    step = {SIGN(direction.x), SIGN(direction.y), SIGN(direction.z)};
    d_delta = step / direction;

    return data;
}
