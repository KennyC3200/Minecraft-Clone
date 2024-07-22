#include "ray.hpp"

void Ray::init(uint64_t **data, float max_distance) {
    this->data = data;
    this->max_distance = max_distance;
}

void Ray::update(glm::vec3 start, glm::vec3 direction) {
    this->start = start;
    this->direction = direction;
}

RayCastData Ray::cast() {
    RayCastData data;

    // algorithm

    return data;
}
