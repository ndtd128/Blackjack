#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

class BaseObject
{
public:
	BaseObject();
	~BaseObject();

	SDL_Texture* getTex() const { return object; }
	SDL_Rect getFrame() const { return frame; }

	void loadTexture(SDL_Renderer* &ren, const std::string& filePath);
	void render(SDL_Renderer* ren, const int& x, const int& y);
	void render(SDL_Renderer* ren, const int& x, const int& y, const int& w, const int& h);
	void render(SDL_Renderer* ren, const int& x, const int& y, const int& w, const int& h, const SDL_Rect& src);

private:
	SDL_Texture* object;
	SDL_Rect frame;
};
