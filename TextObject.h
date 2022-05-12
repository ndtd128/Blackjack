#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class TextObject
{
public:
	TextObject();
	~TextObject();

	enum textColor
	{
		WHITE = 0,
		BLACK = 1,
		RED = 2
	};

	void loadText(SDL_Renderer* ren, TTF_Font* font);
	void render(SDL_Renderer* ren, const int& x, const int& y);

	void setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
	void setColor(const int& type);
	void setContent(const std::string& text) { content = text; }

	int getWidth() const { return width; }
	int getHeight() const { return height; }
	std::string getContent() const { return content; }


private:
	std::string content;
	SDL_Color color;
	SDL_Texture* texture;
	int width;
	int height;
};

static TTF_Font* textFont = nullptr;

static TextObject t_pTotalVal;
static TextObject t_dTotalVal;
static TextObject t_remainCards;