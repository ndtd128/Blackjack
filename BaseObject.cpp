#include "BaseObject.h"

BaseObject::BaseObject()
{
	object = nullptr;
	frame = { 0,0,0,0 };
}

BaseObject::~BaseObject()
{
	if (object != nullptr) {
		SDL_DestroyTexture(object);
		object = nullptr;
		frame = { 0,0,0,0 };
	}
}

void BaseObject::loadTexture(SDL_Renderer* &ren, const std::string& filePath)
{
	object = IMG_LoadTexture(ren, filePath.c_str());
	if (object == nullptr)
		std::cout << "Unable to load texture. Error: " << SDL_GetError() << std::endl;
	SDL_QueryTexture(object, NULL, NULL, &frame.w, &frame.h);
}

void BaseObject::render(SDL_Renderer* ren, const int& x, const int& y)
{
	frame.x = x;
	frame.y = y;
	SDL_RenderCopy(ren, object, NULL, &frame);
}

void BaseObject::render(SDL_Renderer* ren, const int& x, const int& y, const int& w, const int& h)
{
	frame = { x,y,w,h };
	SDL_RenderCopy(ren, object, NULL, &frame);
}

void BaseObject::render(SDL_Renderer* ren, const int& x, const int& y, const int& w, const int& h, const SDL_Rect& src)
{
	frame = { x,y,w,h };
	SDL_RenderCopy(ren, object, &src, &frame);
}
