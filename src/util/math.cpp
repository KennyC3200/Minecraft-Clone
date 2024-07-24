#include "math.hpp"

glm::vec3 intbound(glm::vec3 s, glm::vec3 ds) {
    glm::vec3 v;
    v.x = (ds.x > 0 ? (ceilf(s.x) - s.x) : (s.x - floorf(s.x))) / fabsf(ds.x);
    v.y = (ds.y > 0 ? (ceilf(s.y) - s.y) : (s.y - floorf(s.y))) / fabsf(ds.y);
    v.z = (ds.z > 0 ? (ceilf(s.z) - s.z) : (s.z - floorf(s.z))) / fabsf(ds.z);
    return v;
}
