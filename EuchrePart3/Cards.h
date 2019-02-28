#include "string.h"
#include <iostream>

#ifndef EUCHREPART3_CARDS_H
#define EUCHREPART3_CARDS_H

class Cards
{
public:


	int getValue() const;
	std::string getRank() const;
	std::string getSuit() const;
	bool getRed() const;
	Cards();
	Cards(int Val, std::string Ran, std::string Suit, bool Red);
	~Cards();
protected:
	int value;
	std::string rank;
	std::string suit;
	bool red;
};

#endif 