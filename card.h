#pragma once
#include <string>
#include <iostream>
#include <map>

#include "myEnum.h"

class Card
{
public:
	
	Card(const Value& p_value, const Suit& p_suit);
	~Card() {}

	std::string toString();
	void print();
	Value getValue() { return value; }

private:
	Value value;
	Suit suit;
};

