#include "pch.h"
#include "GameBoard.h"


void GameBoard::gameTable()
{

	buildCardDeck();
	chooseDealer(false, true, false, false);
	std::cout << "Trump suit: " << getTrumpSuitString() << std::endl;
	ai1PlayRound();
	
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

void GameBoard::discardTableHand() {
	player.removeCardPlaced();
	ai1.removeCardPlaced();
	ai2.removeCardPlaced();
	ai3.removeCardPlaced();
}

void GameBoard::playerAddToTableHand() 
{
	player.userChoosesCardToPlay(getTrumpSuitString(), getTrumpRed());
	playerCardValue = checkTableHandValues(player.getCardThatIsChosenToPlay((player.getIndexOfCardThatIsChosenToPlay(player.getChosenCardSuit(), player.getChosenCardRank()))));
}

void GameBoard::ai1AddToTableHand()
{
	ai1.userChoosesCardToPlay(getTrumpSuitString(), getTrumpRed());
	ai1CardValue = checkTableHandValues(ai1.getCardThatIsChosenToPlay(ai1.getIndexOfCardThatIsChosenToPlay(ai1.getChosenCardSuit(), ai1.getChosenCardRank())));
}

void GameBoard::ai2AddToTableHand()
{
	ai2.userChoosesCardToPlay(getTrumpSuitString(), getTrumpRed());
	ai2CardValue = checkTableHandValues(ai2.getCardThatIsChosenToPlay(ai2.getIndexOfCardThatIsChosenToPlay(ai2.getChosenCardSuit(), ai2.getChosenCardRank())));
}

void GameBoard::ai3AddToTableHand()
{
	ai3.userChoosesCardToPlay(getTrumpSuitString(), getTrumpRed());
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

void GameBoard::theWinner()
{
	determineHandWinner(
		player.getCardThatIsChosenToPlay(player.getIndexOfCardThatIsChosenToPlay(player.getChosenCardSuit(), player.getChosenCardRank())),
		ai1.getCardThatIsChosenToPlay(ai1.getIndexOfCardThatIsChosenToPlay(ai1.getChosenCardSuit(), ai1.getChosenCardRank())),
		ai2.getCardThatIsChosenToPlay(ai2.getIndexOfCardThatIsChosenToPlay(ai2.getChosenCardSuit(), ai2.getChosenCardRank())),
		ai3.getCardThatIsChosenToPlay(ai3.getIndexOfCardThatIsChosenToPlay(ai3.getChosenCardSuit(), ai3.getChosenCardRank())));
}

void GameBoard::playerPlayRound() {
	
		for (int i = 0; i < 5; ++i) {
			playerDealer();
			theWinner();
			discardTableHand();
		}
}

void GameBoard::ai1PlayRound() {
	for(int i = 0; i < 5; ++i){
		AI1Dealer();
		theWinner();
		discardTableHand();
	}
}

void GameBoard::ai2PlayRound() {
	for(int i = 0; i < 5; ++i){
		AI2Dealer();
		theWinner();
		discardTableHand();
	}
}

void GameBoard::ai3PlayRound() {
	for(int i = 0; i < 5; ++i){
		AI3Dealer();
		theWinner();
		discardTableHand();
	}
}

///Take in  trump suit and the card value given ranking theem
void GameBoard::determineHandWinner(Cards playerCard, Cards ai1Card, Cards ai2Card, Cards ai3Card)
{
	bool team1Win = false;
	if (playerCardValue > ai1CardValue) {
		if (playerCardValue > ai3CardValue) {
			team1Win = true;
		}
		else {
			team1Win = false;
		}
	}

	if (playerCardValue > ai3CardValue) {
		if (playerCardValue > ai1CardValue) {
			team1Win = true;
		}
		else {
			team1Win = false;
		}
	}

	if (ai2CardValue > ai1CardValue) {
		if (ai2CardValue > ai3CardValue) {
			team1Win = true;
		}
		else {
			team1Win = false;
		}
	}


	if (ai2CardValue > ai3CardValue) {
		if (ai2CardValue > ai1CardValue) {
			team1Win = true;
		}
		else {
			team1Win = false;
		}
	}

	if (playerCardValue > ai1CardValue && playerCard.getSuit() == getTrumpSuitString()) {
		if (playerCardValue > ai3CardValue && playerCard.getSuit() == getTrumpSuitString()) {
			team1Win = true;
		}
		else {
			team1Win = false;
		}
	}

	if (playerCardValue > ai3CardValue && playerCard.getSuit() == getTrumpSuitString()) {
		if (playerCardValue > ai1CardValue && playerCard.getSuit() == getTrumpSuitString()) {
			team1Win = true;
		}
		else {
			team1Win = false;
		}
	}
	
	if (ai2CardValue > ai1CardValue && ai2Card.getSuit() == getTrumpSuitString()) {
		if (ai2CardValue > ai3CardValue && ai2Card.getSuit() == getTrumpSuitString()) {
			team1Win = true;
		}
		else {
			team1Win = false;
		}
	}

	if (ai2CardValue > ai3CardValue && ai2Card.getSuit() == getTrumpSuitString()) {
		if (ai2CardValue > ai1CardValue && ai2Card.getSuit() == getTrumpSuitString()) {
			team1Win = true;
		}
		else {
			team1Win = false;
		}
	}



	if (team1Win) {
		team1Check++;
		std::cout << "Team 1 Wins!" << std::endl;
	}
	else {
		team2Check++;
		std::cout << "Team 2 Wins!" << std::endl;
	}
}


void GameBoard::chooseDealer(bool player, bool ai1, bool ai2, bool ai3)
{
	if (player) {
		std::cout << "Player is the dealer" << std::endl;
		playerDeals();
		choosePlayerTrumpSuit();
	}
	else if (ai1) {
		std::cout << "AI1 is the dealer" << std::endl;
		AI1Deals();
		choose1AITrumpSuit();
	}
	else if (ai2) {
		std::cout << "AI2 is the dealer" << std::endl;		
		AI2Deals();
		choose2AITrumpSuit();
	}
	else if (ai3) {
		std::cout << "AI3 is the dealer" << std::endl;
		AI3Deals();
		choose3AITrumpSuit();
	}

}

void GameBoard::playerDealer()
{
	ai1AddToTableHand();
	ai2AddToTableHand();
	ai3AddToTableHand();
	playerAddToTableHand();
}

void GameBoard::AI1Dealer()
{
	ai2AddToTableHand();
	ai3AddToTableHand();
	playerAddToTableHand();
	ai1AddToTableHand();
}

void GameBoard::AI2Dealer()
{
	ai3AddToTableHand();
	ai1AddToTableHand();
	playerAddToTableHand();
	ai2AddToTableHand();
}

void GameBoard::AI3Dealer()
{
	playerAddToTableHand();
	ai1AddToTableHand();
	ai2AddToTableHand();
	ai3AddToTableHand();
}


void GameBoard::playerDeals()
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

void GameBoard::AI1Deals()
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

void GameBoard::AI2Deals()
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

void GameBoard::AI3Deals()
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
	std::cout << "Top Card: " << tableDeck.trumpCard() << std::endl;
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

//Future Luke, see if you can condense these 4 methods into one. 
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

void GameBoard::theDecisionOfTrumpCard() {
	player.decisionOnTrumpCard(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
	ai1.decisionOnTrumpCard(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
	ai2.decisionOnTrumpCard(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
	ai3.decisionOnTrumpCard(tableDeck.trumpCard(), tableDeck.showTrumpSuit());
}

//ALLL these functions below with choose... are the same just switched the order of players
void GameBoard::choose1AITrumpSuit()
{
	theDecisionOfTrumpCard();
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
	theDecisionOfTrumpCard();
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
	theDecisionOfTrumpCard();
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
	theDecisionOfTrumpCard();
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



