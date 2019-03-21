#include "pch.h"
#include "GameBoard.h"

void GameBoard::gameTable()
{
	buildCardDeck();
	AI1Dealer();
	topCardSuit();
	player.showHand("Player hand:");
	std::cout << "======================================" << std::endl;
	ai1.showHand("AI1 hand: ");
	std::cout << "======================================" << std::endl;
	ai2.showHand("AI2 hand: ");
	std::cout << "======================================" << std::endl;
	ai3.showHand("AI3 hand: ");
	choose1AITrumpSuit();
	playerAddToTableHand(getTrumpSuitString());
	ai1AddToTableHand(getTrumpSuitString());
	ai2AddToTableHand(getTrumpSuitString());
	ai3AddToTableHand(getTrumpSuitString());
	std::cout << "Player: " << player.getCardThatIsChosenToPlay(player.getIndexOfCardThatIsChosenToPlay(player.getChosenCardSuit(), player.getChosenCardRank())).getRank() << std::endl;
	std::cout << "ai1: " << ai1.getCardThatIsChosenToPlay(ai1.getIndexOfCardThatIsChosenToPlay(ai1.getChosenCardSuit(), ai1.getChosenCardRank())).getRank() << std::endl;
	std::cout << "ai2: " << ai2.getCardThatIsChosenToPlay(ai2.getIndexOfCardThatIsChosenToPlay(ai2.getChosenCardSuit(), ai2.getChosenCardRank())).getRank() << std::endl;
	std::cout << "ai3: " << ai3.getCardThatIsChosenToPlay(ai3.getIndexOfCardThatIsChosenToPlay(ai3.getChosenCardSuit(), ai3.getChosenCardRank())).getRank() << std::endl;
	//TO DO: PLAYERS ARE NOT PLAYING LEFT BOWER 
	determineHandWinner(
		player.getCardThatIsChosenToPlay(player.getIndexOfCardThatIsChosenToPlay(player.getChosenCardSuit(), player.getChosenCardRank())), 
		ai1.getCardThatIsChosenToPlay(ai1.getIndexOfCardThatIsChosenToPlay(ai1.getChosenCardSuit(), ai1.getChosenCardRank())), 
		ai2.getCardThatIsChosenToPlay(ai2.getIndexOfCardThatIsChosenToPlay(ai2.getChosenCardSuit(), ai2.getChosenCardRank())),
		ai3.getCardThatIsChosenToPlay(ai3.getIndexOfCardThatIsChosenToPlay(ai3.getChosenCardSuit(), ai3.getChosenCardRank())));
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
////TODO note Now that this adds to tableHand, once all players have placed a card then cardValueCheck claass needs to check what is the highest value for each card. 
////Was going to use anothehr vector but I didn't want to bother with it because I wouldn't be able to know who's card is who.
void GameBoard::playerAddToTableHand(std::string suit) 
{
	player.userChoosesCardToPlay(suit);
	playerCardValue = checkTableHandValues(player.getCardThatIsChosenToPlay((player.getIndexOfCardThatIsChosenToPlay(player.getChosenCardSuit(), player.getChosenCardRank()))));
}

void GameBoard::ai1AddToTableHand(std::string suit)
{
	ai1.userChoosesCardToPlay(suit);


	ai1CardValue = checkTableHandValues(ai1.getCardThatIsChosenToPlay(ai1.getIndexOfCardThatIsChosenToPlay(ai1.getChosenCardSuit(), ai1.getChosenCardRank())));
}

void GameBoard::ai2AddToTableHand(std::string suit)
{
	ai2.userChoosesCardToPlay(suit);
	ai2CardValue = checkTableHandValues(ai2.getCardThatIsChosenToPlay(ai2.getIndexOfCardThatIsChosenToPlay(ai2.getChosenCardSuit(), ai2.getChosenCardRank())));

}

void GameBoard::ai3AddToTableHand(std::string suit)
{
	ai3.userChoosesCardToPlay(suit);
	ai3CardValue = checkTableHandValues(ai3.getCardThatIsChosenToPlay(ai3.getIndexOfCardThatIsChosenToPlay(ai3.getChosenCardSuit(), ai3.getChosenCardRank())));

}

int GameBoard::checkTableHandValues(Cards card)
{
	if (card.getSuit() == getTrumpSuitString() && card.getRank() == "Jack") {
		return 9;
	}
	else if (card.getRed() == getTrumpRed() && card.getRank() == "Jack") {
		return 8;
	}
	else {
		return card.getValue();
	}

}

///Take in  trump suit and the card value given ranking theem
void GameBoard::determineHandWinner(Cards playerCard, Cards ai1Card, Cards ai2Card, Cards ai3Card)
{
	bool team1Win = false;
	if (playerCardValue > ai1CardValue && playerCard.getSuit() == getTrumpSuitString()) {
		if (playerCardValue > ai3CardValue && playerCard.getSuit() == getTrumpSuitString()) {
			team1Win = true;
		}
		else {
			team1Win = false;
		}
	}
	
	else if (ai2CardValue > ai1CardValue && ai2Card.getSuit() == getTrumpSuitString()) {
		if (ai2CardValue > ai3CardValue && ai2Card.getSuit() == getTrumpSuitString()) {
			team1Win = true;
		}
		else {
			team1Win = false;
		}
	}

	if (team1Win) {
		team1Check++;
		std::cout << "Team 1 Wins!";
	}
	else {
		team2Check++;
		std::cout << "Team 2 Wins!";
	}
}


///This function isn't needed
void GameBoard::chooseDealer(bool player, bool ai1, bool ai2, bool ai3)
{
	/*if (player) {
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
	}*/

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

//ALLL these functions below with choose... are the same just switched the order of players
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
		ai1.whenTheDealerDoesNotLikeTrumpCard(ai1.numberOfASpecificSuitInHand("Spades"), ai1.numberOfASpecificSuitInHand("Clubs"), ai1.numberOfASpecificSuitInHand("Diamonds"), ai1.numberOfASpecificSuitInHand("Diamonds"));
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
	if (ai3.getShouldThisTopCardBeTrump()) {
		trumpSuit(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
		std::cout << "ai3 chose suit" << std::endl;
		ai2.dealDropsWorstCard(getTrumpRed());
		ai1.acquireCard(tableDeck.drawCard());
	}
	else if (player.getShouldThisTopCardBeTrump()) {
		trumpSuit(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
		std::cout << "player chose suit" << std::endl;
		ai2.dealDropsWorstCard(getTrumpRed());
		ai2.acquireCard(tableDeck.drawCard());
	}
	else if (ai1.getShouldThisTopCardBeTrump()) {
		trumpSuit(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
		std::cout << "ai1 chose suit" << std::endl;
		ai2.dealDropsWorstCard(getTrumpRed());
		ai2.acquireCard(tableDeck.drawCard());
	}
	else if (ai2.getShouldThisTopCardBeTrump()) {
		trumpSuit(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
		std::cout << "ai2 chose suit" << std::endl;
		ai2.dealDropsWorstCard(getTrumpRed());
		ai2.acquireCard(tableDeck.drawCard());
	}
	else {
		ai1.whenTheDealerDoesNotLikeTrumpCard(ai1.numberOfASpecificSuitInHand("Spades"), ai1.numberOfASpecificSuitInHand("Clubs"), ai1.numberOfASpecificSuitInHand("Diamonds"), ai1.numberOfASpecificSuitInHand("Diamonds"));
		trumpSuit(ai2.getSuitTrump(), ai2.getRed());
		std::cout << "Dealer chose suit" << std::endl;
	}
}

void GameBoard::choose3AITrumpSuit()
{
	player.decisionOnTrumpCard(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
	ai1.decisionOnTrumpCard(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
	ai2.decisionOnTrumpCard(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
	ai3.decisionOnTrumpCard(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
	if (player.getShouldThisTopCardBeTrump()) {
		trumpSuit(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
		std::cout << "player chose suit" << std::endl;
		ai3.dealDropsWorstCard(getTrumpRed());
		ai3.acquireCard(tableDeck.drawCard());
	}
	else if (ai1.getShouldThisTopCardBeTrump()) {
		trumpSuit(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
		std::cout << "ai1 chose suit" << std::endl;
		ai3.dealDropsWorstCard(getTrumpRed());
		ai3.acquireCard(tableDeck.drawCard());
	}
	else if (ai2.getShouldThisTopCardBeTrump()) {
		trumpSuit(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
		std::cout << "ai2 chose suit" << std::endl;
		ai3.dealDropsWorstCard(getTrumpRed());
		ai3.acquireCard(tableDeck.drawCard());
	}
	else if (ai3.getShouldThisTopCardBeTrump()) {
		trumpSuit(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
		std::cout << "ai3 chose suit" << std::endl;
		ai3.dealDropsWorstCard(getTrumpRed());
		ai3.acquireCard(tableDeck.drawCard());
	}
	else {
		ai1.whenTheDealerDoesNotLikeTrumpCard(ai1.numberOfASpecificSuitInHand("Spades"), ai1.numberOfASpecificSuitInHand("Clubs"), ai1.numberOfASpecificSuitInHand("Diamonds"), ai1.numberOfASpecificSuitInHand("Diamonds"));
		trumpSuit(ai3.getSuitTrump(), ai3.getRed());
		std::cout << "Dealer chose suit" << std::endl;
	}
}

void GameBoard::choosePlayerTrumpSuit()
{
	ai1.decisionOnTrumpCard(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
	ai2.decisionOnTrumpCard(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
	ai3.decisionOnTrumpCard(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
	player.decisionOnTrumpCard(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
	if (ai1.getShouldThisTopCardBeTrump()) {
		trumpSuit(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
		std::cout << "ai1 chose suit" << std::endl;
		player.dealDropsWorstCard(getTrumpRed());
		player.acquireCard(tableDeck.drawCard());
	}
	else if (ai2.getShouldThisTopCardBeTrump()) {
		trumpSuit(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
		std::cout << "ai2 chose suit" << std::endl;
		player.dealDropsWorstCard(getTrumpRed());
		player.acquireCard(tableDeck.drawCard());
	}
	else if (ai3.getShouldThisTopCardBeTrump()) {
		trumpSuit(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
		std::cout << "ai3 chose suit" << std::endl;
		player.dealDropsWorstCard(getTrumpRed());
		player.acquireCard(tableDeck.drawCard());
	}
	else if (player.getShouldThisTopCardBeTrump()) {
		trumpSuit(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
		std::cout << "player chose suit" << std::endl;
		player.dealDropsWorstCard(getTrumpRed());
		player.acquireCard(tableDeck.drawCard());
	}
	else {
		ai1.whenTheDealerDoesNotLikeTrumpCard(ai1.numberOfASpecificSuitInHand("Spades"), ai1.numberOfASpecificSuitInHand("Clubs"), ai1.numberOfASpecificSuitInHand("Diamonds"), ai1.numberOfASpecificSuitInHand("Diamonds"));
		trumpSuit(player.getSuitTrump(), player.getRed());
		std::cout << "Dealer chose suit" << std::endl;
	}
}


void GameBoard::endTheProcess()
{
	tableDeck.deleteVectors();
}



