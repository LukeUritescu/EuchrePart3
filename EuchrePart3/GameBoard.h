#pragma once
#include "DeckEngine.h"
#include "Cards.h"

#include "User.h"

#include <vector>
#include "string.h"
#include <iostream>


#ifndef EUCHREPART3_GAMEBOARD_H
#define EUCHREPART3_GAMEBOARD_H


class GameBoard
{
public:
	void buildCardDeck();
	Cards dealCards();

	void gameTable();

	void replenishDeck();
	void chooseDealer(bool player = true, bool ai1 = false, bool ai2 = false, bool ai3 = false);
	void trumpSuit(std::string suit, bool red);
	void topCardSuit();

	void playerPass(int numberCardDeal = 3);
	void AI1Pass(int numberCardDeal = 3);
	void AI2Pass(int numberCardDeal = 3);
	void AI3Pass(int numberCardDeal = 3);

	void playerDealer();
	void AI1Dealer();
	void AI2Dealer();
	void AI3Dealer();

	void choosePlayerTrumpSuit();
	void choose1AITrumpSuit();
	void choose2AITrumpSuit();
	void choose3AITrumpSuit();

	std::string getTrumpSuitString();
	bool getTrumpRed();


	void endTheProcess();

protected:
	DeckEngine tableDeck;
	User player;
	User ai1;
	User ai2;
	User ai3;
	std::string trumpSuitString;
	bool trumpRed;
	bool red = false;
};

#endif // !EUCHRE_GAMEBOARD_H

