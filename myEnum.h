#pragma once

 enum class Value {
	BEGIN, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE, END
};
 enum class Suit {
	BEGIN, SPADE, CLUB, DIAMOND, HEART, END
};

 enum class	gameScene {
	 PLAYER_PHASE, DEALER_PHASE
 };

 enum class gameResult {
	 BEGIN, CONTINUE, P_BLACK_JACK, D_BLACK_JACK, PUSH, WIN, LOSE, P_BUSTS, D_BUSTS
 };

inline Value& operator ++ (Value& e)
{
	e = Value(static_cast<std::underlying_type<Value>::type>(e) + 1);
	return e;
}

inline std::string toStr(const Value& v)
{
	const std::map<const Value, const std::string> valMap{
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
	auto it = valMap.find(v);
	if (it != valMap.end())
		return it->second;
	else return "Out of range!";
}

inline int toInt(const Value& v)
{
	const std::map<const Value, const int> valMap{
		{Value::ACE, 1},
		{Value::TWO, 2},
		{Value::THREE, 3},
		{Value::FOUR, 4},
		{Value::FIVE, 5},
		{Value::SIX, 6},
		{Value::SEVEN, 7},
		{Value::EIGHT, 8},
		{Value::NINE, 9},
		{Value::TEN, 10},
		{Value::JACK, 11},
		{Value::QUEEN, 12},
		{Value::KING, 0}
	};

	auto it = valMap.find(v);
	if (it != valMap.end())
		return it->second;
	return -1;
}

inline Suit& operator ++ (Suit& e)
{
	e = Suit(static_cast<std::underlying_type<Suit>::type>(e) + 1);
	return e;
}

inline std::string toStr(const Suit& s)
{
	const std::map<const Suit, const std::string> suitMap{
		{Suit::SPADE, "SPADE"},
		{Suit::CLUB, "CLUB"},
		{Suit::DIAMOND, "DIAMOND"},
		{Suit::HEART, "HEART"}
	};
	auto it = suitMap.find(s);
	if (it != suitMap.end())
		return it->second;
	else return "Out of range";
}

inline int toInt(const Suit& s)
{
	const std::map<const Suit, const int> suitMap{
	{Suit::SPADE, 0},
	{Suit::CLUB, 1},
	{Suit::DIAMOND, 2},
	{Suit::HEART, 3}
	};
	auto it = suitMap.find(s);
	if (it != suitMap.end())
		return it->second;
	else return -1;
}