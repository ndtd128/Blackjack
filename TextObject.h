#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

#include "myEnum.h"

class TextObject
{
public:
	TextObject();
	~TextObject();



	void loadText(SDL_Renderer* ren, TTF_Font* font);
	void render(SDL_Renderer* ren, const int& x, const int& y);

	void setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
	void setColor(const int& type);
	void setContent(const std::string& text) { content = text; }

	int getWidth() const { return width; }
	int getHeight() const { return height; }
	std::string getContent() const { return content; }

	bool checkFocus(const SDL_Point& m_pos, const SDL_Point& button_pos);
private:
	std::string content;
	SDL_Color color;
	SDL_Texture* texture;
	int width;
	int height;
};