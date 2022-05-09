#pragma once
#include <SDL.h>

//Window
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char WINDOW_TITLE[] = "Blackjack";

//Game starter pack
const int PLAYER_START_CASH = 100;

const int FULL_DECK_SIZE = 52;
const int MAX_PLAYER_CARDS = 12;
const int CARD_WIDTH = 90;
const int CARD_HEIGHT = CARD_WIDTH * 3 / 2;
const int CARD_XSPACE = CARD_WIDTH / 3;
const int CARD_YSPACE = CARD_HEIGHT / 2;
