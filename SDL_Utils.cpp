#include "SDL_Utils.h"

bool init(SDL_Window* &window, SDL_Renderer* &renderer, const int& p_w, const int& p_h, 
          const char p_title[], const char iconFile[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "SDL Init has failed. Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) < 0) {
        std::cout << "IMG Init has failed. Error: " << IMG_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() < 0) {
        std::cout << "TTF Init has failed. Error: " << TTF_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                p_w, p_h, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cout << "Unable to create window. Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_Surface* iconSur = IMG_Load(iconFile);
    SDL_SetWindowIcon(window, iconSur);
    SDL_FreeSurface(iconSur);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cout << "Unable to create renderer. Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    return true;
}

void kill(SDL_Window* &window, SDL_Renderer* &renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}

void clear(SDL_Renderer* &ren)
{
    SDL_RenderClear(ren);
}

void display(SDL_Renderer* &ren)
{
    SDL_RenderPresent(ren);
}
