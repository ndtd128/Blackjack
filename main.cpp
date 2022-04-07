#include "RenderWindow.hpp"
#include "gameConstants.h"


int main(int argc, char* argv[])
{
    RenderWindow window(WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        window.renderClear();
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
                break;
            }
        }
        SDL_Texture* table = window.loadTexture("image/table.png");
        window.render(0, 0, table);
        SDL_DestroyTexture(table);
        window.display();
    }
    window.quit();

    return 0;
}