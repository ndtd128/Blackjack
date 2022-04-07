#ifndef RENDERWINDOW_HPP_INCLUDED
#define RENDERWINDOW_HPP_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>


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
    void render(const int& x, const int& y, SDL_Texture* tex);
    

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};



#endif // RENDERWINDOW_HPP_INCLUDED
