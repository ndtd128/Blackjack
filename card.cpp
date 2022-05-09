#include "card.h"
#include "myEnum.h"

Card::Card(const Value& p_value, const Suit& p_suit)
{
	value = p_value;
	suit = p_suit;
}

std::string Card::valString()
{
	return toStr(value);
}

std::string Card::suitString()
{
	return toStr(suit);
}

std::string Card::toString()
{
	return valString() + "-" + suitString();
}

void Card::print()
{
	std::cout << toString() << std::endl;
}