#pragma once
#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Cards.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>

#ifndef EUCHREPART3_DECKENGINE_H
#define EUCHREPART3_DECKENGINE_H

class DeckEngine
{

public:
	void createDeck();
	void shuffle();
	Cards drawCard();
	bool showTrumpSuit();
	void printDeck();
	int getIndex();

	bool emptyDeck();


	std::vector<Cards>* drawnCards;
	void deleteVectors();
	std::string trumpCard();

protected:
	int index;
	int value;
	std::string rank;
	std::string suit;
	bool red;
	std::vector<Cards>* deckOfCards;

};
#endif


