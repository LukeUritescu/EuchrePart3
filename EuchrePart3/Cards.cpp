#include "pch.h"
#include "Cards.h"

int Cards::getValue() const
{
	return value;
}
std::string Cards::getRank() const
{
	return rank;
}
std::string Cards::getSuit() const
{
	return suit;
}

bool Cards::getRed() const
{
	return red;
}


Cards::Cards(int Val, std::string Ran, std::string Suit, bool Red)
{
	value = Val;
	rank = Ran;
	suit = Suit;
	red = Red;

}

Cards::Cards() {}

Cards::~Cards()
{
}
