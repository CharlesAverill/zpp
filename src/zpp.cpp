#include "GameManager.h"

const int WIDTH = 1920;
const int HEIGHT = 1080;

int main() {
    GameManager gm;

    gm.init_window(WIDTH, HEIGHT);
    gm.game_loop();

    return 0;
}
