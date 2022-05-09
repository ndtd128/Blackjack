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
	int deckSize() { return deck.size(); }
	void print();
	void shuffle();
	Card getCard(const int& pos);
	void removeCard(const int& pos);
	void addCard(const Card& p_card);
	void addCard(const Value& v, const Suit& s);
	void draw(Deck& comingFrom);
	void moveAllToDeck(Deck& moveTo);
	int getTotalValue(); //return total value of cards in deck
	

private:
	std::vector<Card> deck;
};