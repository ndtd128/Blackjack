#include <iostream>


#include "RenderWindow.hpp"

/**************************/

RenderWindow::RenderWindow(const std::string& p_title, int p_w, int p_h)
    :window(nullptr), renderer(nullptr)
{
    if (!init()) {
        std::cout << "Initialize has failed." << std::endl;
        exit(1);
    }

    window = SDL_CreateWindow(p_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, p_w, p_h,SDL_WINDOW_SHOWN);
    if(window == nullptr)
        std::cout << "Unable to create window. Error: " << SDL_GetError() << std::endl;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
        std::cout << "Unable to create renderer. Error: " << SDL_GetError() << std::endl;
}

RenderWindow::~RenderWindow()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

bool RenderWindow::init()
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
    return true;
}

void RenderWindow::quit()
{
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}

SDL_Texture* RenderWindow::loadTexture (const std::string& p_filePath)
{
    SDL_Texture* texture = nullptr;
    texture = IMG_LoadTexture(renderer, p_filePath.c_str());

    if(texture == nullptr)
        std::cout << "Failed to load a texture. Error: " << SDL_GetError() << std::endl;

    return texture;
}

void RenderWindow::renderClear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}

void RenderWindow::render(const int& x, const int& y, BaseObject obj)
{

    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = obj.getFrame().w;
    dst.h = obj.getFrame().h;


    SDL_RenderCopy(renderer, obj.getTex(), NULL, &dst);
}

void RenderWindow::render(const int& x, const int& y, const int& w, const int& h, BaseObject obj)
{
    SDL_Rect dst = { x,y,w,h };

    SDL_RenderCopy(renderer, obj.getTex(), NULL, &dst);
}
