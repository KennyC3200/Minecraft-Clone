#include "mouse.h"

glm::vec2 Mouse::GetPosition() {
    return position;
}

glm::vec2 Mouse::GetPositionDelta() {
    return position_delta;
}
