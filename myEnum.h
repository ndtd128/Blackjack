#pragma once

 enum class Value {
	BEGIN, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE, END
};
 enum class Suit {
	BEGIN, SPADE, CLUB, DIAMOND, HEART, END
};


inline Value& operator ++ (Value& e)
{
	e = Value(static_cast<std::underlying_type<Value>::type>(e) + 1);
	return e;
}

inline Suit& operator ++ (Suit& e)
{
	e = Suit(static_cast<std::underlying_type<Suit>::type>(e) + 1);
	return e;
}

