#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define MAX(a, b) ({       \
    __typeof__ (a) _a = a; \
    __typeof__ (b) _b = b; \
    _a > _b ? _a : _b; })

#define MIN(a, b) ({       \
    __typeof__ (a) _a = a; \
    __typeof__ (b) _b = b; \
    _a < _b ? _a : _b; })

#define CLAMP(x, x_min, x_max) ({        \
    __typeof__ (x) _x = (x);             \
    __typeof__ (x_min) _x_min = (x_min); \
    __typeof__ (x_max) _x_max = (x_max); \
    MAX(_x_min, MIN(_x_max, _x)); })
