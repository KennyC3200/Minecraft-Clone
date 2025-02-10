#include "crosshair.h"

void Crosshair::Init() {
    texture.Init("../res/images/crosshair.png", "tex", GL_RGBA, GL_RGBA);
    toggled = true;
}
