#pragma once
#include <vector>
#include "card.h"
//#include "gameConstants.h"

class Deck
{
public:
	Deck() {}
	~Deck() {}

	void createFullDeck();
	std::string toString();
	void print();
	void shuffle();
	Card getCard(const int& pos);
	void removeCard(const int& pos);
	void addCard(const Card& p_card);
	void draw(Deck& comingFrom);
	

private:
	std::vector<Card> deck;
};