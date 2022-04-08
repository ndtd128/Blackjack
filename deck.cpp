#include "Deck.h"

void Deck::createFullDeck()
{
	for (Value v = Value::BEGIN; v != Value::END; ++v) {
		if (v == Value::BEGIN) continue;
		for (Suit s = Suit::BEGIN; s != Suit::END; ++s) {
			if (s == Suit::BEGIN) continue;
			Card newCard(v, s);
			deck.push_back(newCard);
		}
	}
}

std::string Deck::toString()
{
	std::string cardList = "";
	//unsigned int i = 0;

	for (auto c : deck) {
		cardList += '\n' /* + std::to_string(i)*/ + c.toString();
		//i++;
	}

	return cardList;
}

void Deck::print()
{
	std::cout << toString() << std::endl;
}

void Deck::shuffle()
{
	
	std::vector<Card> tmpDeck;
	const int& originSize = deck.size();
	int randomNum = -1;
	for (unsigned int i = 0; i < originSize; ++i) {
		randomNum = rand() % deck.size();
		//Card tmpCard = deck[randomNum]
		tmpDeck.push_back(deck[randomNum]);
		deck.erase(deck.begin() + randomNum);
	}
	for (auto c : tmpDeck) {
		deck.push_back(c);
	}
}

Card Deck::getCard(const int& pos)
{
	return deck[pos];
}

void Deck::removeCard(const int& pos)
{
	deck.erase(deck.begin() + pos);
}

void Deck::addCard(const Card& p_card)
{
	deck.push_back(p_card);
}

void Deck::draw(Deck& comingFrom)
{
	//0 mean top of the deck that we draw
	deck.push_back(comingFrom.getCard(0));
	comingFrom.removeCard(0);
}
