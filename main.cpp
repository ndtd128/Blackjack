#include <stdlib.h>
#include <time.h>

#include "Game.h"

int main(int argc, char* argv[])
{
    srand(time(0));
    static Game blackJack(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE, ICON_FILE_PATH);
    int playerChoice = blackJack.showMenu();
    if (playerChoice == PLAY) {
        blackJack.startNewGame();
    }
    blackJack.kill();

    return 0;
}