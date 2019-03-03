#include "pch.h"
#include "GameBoard.h"

void GameBoard::gameTable()
{
	buildCardDeck();
	chooseDealer(false, true, false, false);
	topCardSuit();
	player.showHand("Player hand:");
	std::cout << "======================================" << std::endl;
	ai1.showHand("AI1 hand: ");
	std::cout << "======================================" << std::endl;
	ai2.showHand("AI2 hand: ");
	std::cout << "======================================" << std::endl;
	ai3.showHand("AI3 hand: ");
	choose1AITrumpSuit();

	ai1.showHand("AI1 hand2");
}

void GameBoard::buildCardDeck()
{
	tableDeck.createDeck();
	tableDeck.shuffle();
}

Cards GameBoard::dealCards()
{
	replenishDeck();
	return tableDeck.drawCard();
}

void GameBoard::replenishDeck()
{
	if (tableDeck.emptyDeck()) {
		buildCardDeck();
	}
}

void GameBoard::addToTableHand(Cards card) 
{
	tableHand->push_back(card);
}

void GameBoard::deleteTableHand()
{
	delete tableHand;
}

void GameBoard::chooseDealer(bool player, bool ai1, bool ai2, bool ai3)
{
	if (player) {
		std::cout << "Player is the dealer" << std::endl;
		playerDealer();
		choosePlayerTrumpSuit();
	}
	else if (ai1) {
		AI1Dealer();
	}
	else if (ai2) {
		AI2Dealer();
		choose2AITrumpSuit();
	}
	else if (ai3) {
		AI3Dealer();
		choose3AITrumpSuit();
	}

}

void GameBoard::wholeUp()
{

}

void GameBoard::playerDealer()
{
	//first pass default 3 cards
	AI1Pass();
	AI2Pass();
	AI3Pass();
	playerPass();
	//second pass 2 cards
	AI1Pass(2);
	AI2Pass(2);
	AI3Pass(2);
	playerPass(2);
}

void GameBoard::AI1Dealer()
{
	//first pass default 3 cards
	AI2Pass();
	AI3Pass();
	playerPass();
	AI1Pass();
	//second pass 2 cards
	AI2Pass(2);
	AI3Pass(2);
	playerPass(2);
	AI1Pass(2);
}

void GameBoard::AI2Dealer()
{
	//first pass default 3 cards
	AI3Pass();
	playerPass();
	AI1Pass();
	AI2Pass();
	//second pass 2 cards
	AI3Pass(2);
	playerPass(2);
	AI1Pass(2);
	AI2Pass(2);
}

void GameBoard::AI3Dealer()
{
	//first pass default 3 cards
	playerPass();
	AI1Pass();
	AI2Pass();
	AI3Pass();
	//second pass 2 cards
	playerPass(2);
	AI1Pass(2);
	AI2Pass(2);
	AI3Pass(2);
}


void GameBoard::topCardSuit()
{
	std::cout << "Trump Suit: " << tableDeck.trumpCard() << std::endl;
	if (tableDeck.trumpCard() == "Diamonds" || tableDeck.trumpCard() == "Hearts")
		red = true;
	else
		red = false;
}

std::string GameBoard::getTrumpSuitString()
{
	return trumpSuitString;
}

bool GameBoard::getTrumpRed()
{
	return trumpRed;
}

void GameBoard::trumpSuit(std::string suit, bool red)
{
	trumpSuitString = suit;
	trumpRed = red;
}

//Future Luke, see if yo can condense these 4 methods into one. 
void GameBoard::playerPass(int numberCardDeal)
{
	for (int i = 0; i < numberCardDeal; i++) {
		player.acquireCard(dealCards());
	}
}

void GameBoard::AI1Pass(int numberCardDeal)
{
	for (int i = 0; i < numberCardDeal; i++) {
		ai1.acquireCard(dealCards());
	}
}

void GameBoard::AI2Pass(int numberCardDeal)
{
	for (int i = 0; i < numberCardDeal; i++) {
		ai2.acquireCard(dealCards());
	}
}

void GameBoard::AI3Pass(int numberCardDeal)
{
	for (int i = 0; i < numberCardDeal; i++) {
		ai3.acquireCard(dealCards());
	}
}

void GameBoard::choose1AITrumpSuit()
{
	ai2.decisionOnTrumpCard(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
	player.decisionOnTrumpCard(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
	ai3.decisionOnTrumpCard(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
	ai1.decisionOnTrumpCard(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
	if (ai2.getShouldThisTopCardBeTrump()) {
		trumpSuit(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
		std::cout << "ai2 chose suit" << std::endl;
		ai1.dealDropsWorstCard(getTrumpRed());
		ai1.acquireCard(tableDeck.drawCard());
	}
	else if (ai3.getShouldThisTopCardBeTrump()) {
		trumpSuit(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
		std::cout << "ai3 chose suit" << std::endl;
		ai1.dealDropsWorstCard(getTrumpRed());
		ai1.acquireCard(tableDeck.drawCard());
	}
	else if (player.getShouldThisTopCardBeTrump()) {
		trumpSuit(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
		std::cout << "player chose suit" << std::endl;
		ai1.dealDropsWorstCard(getTrumpRed());
		ai1.acquireCard(tableDeck.drawCard());
	}
	else if (ai1.getShouldThisTopCardBeTrump()) {
		trumpSuit(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
		std::cout << "ai1 chose suit" << std::endl;
		ai1.dealDropsWorstCard(getTrumpRed());
		ai1.acquireCard(tableDeck.drawCard());
	}
	else {
		ai1.whenTheDealerDoesNotLikeTrumpCard(ai1.numberOfSpadesInHand(), ai1.numberOfClubsInHand(), ai1.numberOfDiamondsInHand(), ai1.numberOfHeartsInHand());
		trumpSuit(ai1.getSuitTrump(), ai1.getRed());
		std::cout << "Dealer chose suit" << std::endl;
	}

}

void GameBoard::choose2AITrumpSuit()
{
	ai3.decisionOnTrumpCard(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
	player.decisionOnTrumpCard(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
	ai1.decisionOnTrumpCard(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
	ai2.decisionOnTrumpCard(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
}

void GameBoard::choose3AITrumpSuit()
{
	player.decisionOnTrumpCard(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
	ai1.decisionOnTrumpCard(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
	ai2.decisionOnTrumpCard(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
	ai3.decisionOnTrumpCard(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
}

void GameBoard::choosePlayerTrumpSuit()
{
	ai1.decisionOnTrumpCard(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
	ai2.decisionOnTrumpCard(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
	ai3.decisionOnTrumpCard(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
	player.decisionOnTrumpCard(tableDeck.trumpCard(), tableDeck.showTrumpSuit());

}


void GameBoard::endTheProcess()
{
	tableDeck.deleteVectors();
}



