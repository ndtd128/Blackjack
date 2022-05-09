#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

#include "BaseObject.h"

class RenderWindow
{
public:
    RenderWindow(const std::string& p_title, int p_w, int p_h);
    ~RenderWindow();

    bool init();
    void quit();

    SDL_Texture* loadTexture (const std::string& p_filePath);
    void renderClear();
    void display();
    void render(const int& x, const int& y, BaseObject obj);
    void render(const int& x, const int& y, const int& w, const int& h, BaseObject obj);
    

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

