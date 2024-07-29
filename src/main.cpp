#include "game.hpp"

int main(int argc, char *argv[]) {
    Game game;
    game.init();
    game.loop();
    game.destroy();
    return 0;
}
