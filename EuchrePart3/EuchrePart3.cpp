// EuchrePart3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "GameBoard.h"

int main()
{
	srand(time(NULL));
	GameBoard deckofCards;
	deckofCards.gameTable();
	std::cin;
	deckofCards.endTheProcess();
	deckofCards.deleteTableHand();
}

