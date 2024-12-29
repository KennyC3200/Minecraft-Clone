#include "game.h"

int main() {
    Game game;
    game.init();
    game.loop();
    game.destroy();
    return 0;
}
