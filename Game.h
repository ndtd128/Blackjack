#pragma once
#include <SDL_mixer.h>

#include "gameConstants.h"
#include "Deck.h"
#include "BaseObject.h"
#include "TextObject.h"

class Game
{
public:
	Game(const int& p_w, const int& p_h, const char p_title[], const char iconFile[]);
	~Game();

	bool init(const int& p_w, const int& p_h, const char p_title[], const char iconFile[]);
	void loadMedia();
	void renderScene();
	void kill();

	void clear();
	void display();

	int showMenu();
	void startNewGame();
	void betting();
	void playOneRound();
	void dealerTurn();
	int endGame();
	bool gameOver();
private:
	Deck mainDeck, playerDeck, dealerDeck;
	int dVal, pVal;
	int bank;
	int bet;
	std::string input;
	gameScene scene;
	gameResult res;
	bool quit;

	SDL_Window* window;
	SDL_Renderer* renderer;

	BaseObject background;
	BaseObject table;
	BaseObject menuTitle;
	BaseObject result;
	BaseObject cardObj[13][4];
	BaseObject backCard;
	BaseObject cardIcon;

	TTF_Font* textFont;
	TextObject t_menuButton[menuItem];
	TextObject t_pTotalVal;
	TextObject t_dTotalVal;
	TextObject t_remainCards;

	//SDL_Rect cursor{ 0, 0, 1, 1 };
	Mix_Music* music;
};