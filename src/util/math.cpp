#include "math.hpp"

glm::vec3 intbound(glm::vec3 s, glm::vec3 ds) {
    glm::vec3 v;
    for (size_t i = 0; i < 3; i++) {
        v[i] = (ds[i] > 0 ? (ceilf(s[i]) - s[i]) : (s[i] - floorf(s[i]))) / fabsf(ds[i]);
    }
    return v;
}
