#include "TextObject.h"

TextObject::TextObject()
{
	texture = nullptr;
	color = { 255,255,255,255 };//white
	width = 0;
	height = 0;
	content = "";
}

TextObject::~TextObject()
{
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

void TextObject::loadText(SDL_Renderer* ren, TTF_Font* font)
{
	SDL_Surface* textSur = TTF_RenderText_Solid(font, content.c_str(), color);
	texture = SDL_CreateTextureFromSurface(ren, textSur);
	width = textSur->w;
	height = textSur->h;

	SDL_FreeSurface(textSur);
	if (texture == nullptr)
		std::cout << "Unable to load text: " << content << ". Error:" << SDL_GetError() << std::endl;
}

void TextObject::render(SDL_Renderer* ren, const int& x, const int& y)
{
	SDL_Rect dst = { x,y,width,height };
	SDL_RenderCopy(ren, texture, NULL, &dst);
}

void TextObject::setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 255)
{
	color = { red,green,blue,alpha };
}

void TextObject::setColor(const int& type)
{
	switch (type)
	{
	case WHITE:
		color = { 255,255,255,255 };
		break;
	case BLACK:
		color = { 0,0,0,255 };
		break;
	case RED:
		color = { 255,0,0,255 };
		break;
	default:
		color = { 255,255,255,255 };
		break;
	}
}
