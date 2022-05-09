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

void Deck::addCard(const Value& v, const Suit& s)
{
	deck.push_back(Card(v, s));
}

void Deck::draw(Deck& comingFrom)
{
	//0 mean top of the deck that we draw
	deck.push_back(comingFrom.getCard(0));
	comingFrom.removeCard(0);
}

void Deck::moveAllToDeck(Deck& moveTo)
{
	int deckSize = deck.size();
	for (size_t i = 0; i < deckSize; ++i)
	{
		moveTo.addCard(deck[i]);
	}
	
	deck.erase(deck.begin(), deck.end());
}

int Deck::getTotalValue()
{
	int totalValue = 0;
	int aceCnt = 0;
	for (auto c : deck) {
		switch (c.getValue())
		{
		case Value::TWO:
			totalValue += 2;
			break;
		case Value::THREE:
			totalValue += 3;
			break;
		case Value::FOUR:
			totalValue += 4;
			break;
		case Value::FIVE:
			totalValue += 5;
			break;
		case Value::SIX:
			totalValue += 6;
			break;
		case Value::SEVEN:
			totalValue += 7;
			break;
		case Value::EIGHT:
			totalValue += 8;
			break;
		case Value::NINE:
			totalValue += 9;
			break;
		case Value::TEN:
		case Value::JACK:
		case Value::QUEEN:
		case Value::KING:
			totalValue += 10;
			break;
		case Value::ACE:
			++aceCnt;
			break;
		default:
			break;
		}
	}

	for (size_t i = 0; i < aceCnt; i++)
	{
		if (totalValue > 10)
			totalValue += 1;
		else totalValue += 11;
	}

	return totalValue;
}
