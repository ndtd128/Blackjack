#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>

bool init(SDL_Window* &window, SDL_Renderer* &renderer, const int& p_w, const int& p_h, const char p_title[], const char iconFile[]);
void kill(SDL_Window* &window, SDL_Renderer* &renderer);

void clear(SDL_Renderer* &ren);
void display(SDL_Renderer* &ren);