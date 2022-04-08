#include "card.h"

Card::Card(const Value& p_value, const Suit& p_suit)
{
	value = p_value;
	suit = p_suit;
}

std::string Card::toString()
{
	std::string str_suit = "", str_val = "", res = "";

	const std::map<const Value, const std::string> valMap {
		{Value::TWO, "TWO"},
		{Value::THREE, "THREE"},
		{Value::FOUR, "FOUR"},
		{Value::FIVE, "FIVE"},
		{Value::SIX, "SIX"},
		{Value::SEVEN, "SEVEN"},
		{Value::EIGHT, "EIGHT"},
		{Value::NINE, "NINE"},
		{Value::TEN, "TEN"},
		{Value::JACK, "JACK"},
		{Value::QUEEN, "QUEEN"},
		{Value::KING, "KING"},
		{Value::ACE, "ACE"}
	};
	auto it1 = valMap.find(value);
	if (it1 != valMap.end())
		str_val = it1->second;
	else return "Out of range";

	const std::map<const Suit, const std::string> suitMap {
		{Suit::SPADE, "SPADE"},
		{Suit::CLUB, "CLUB"},
		{Suit::DIAMOND, "DIAMOND"},
		{Suit::HEART, "HEART"}
	};
	auto it2 = suitMap.find(suit);
	if (it2 != suitMap.end())
		str_suit = it2->second;
	else return "Out of range";
	
	res = str_val + "-" + str_suit;

	return res;
}

void Card::print()
{
	std::cout << toString() << std::endl;
}