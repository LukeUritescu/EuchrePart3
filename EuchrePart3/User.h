#pragma 
#ifndef EUCHREPART3_USER_H
#define EUCHREPART3_USER_H

#include <iostream>
#include <string>
#include <vector>

#include "Cards.h"
#include "DeckEngine.h"
class User
{
public:
	void acquireCard(Cards card);
	void showHand(std::string name);

	bool findJackInHand();
	bool hasJackSameSuitColor(std::string suit, bool red);
	bool hasJackTrumpSuit(std::string suit);

	void decisionOnTrumpCard(std::string suit, bool red);

	bool getShouldThisTopCardBeTrump();

	void whenTheDealerDoesNotLikeTrumpCard(int spades, int clubs, int diamonds, int hearts);

	std::string getSuitTrump();
	bool getRed();

	void dealDropsWorstCard(bool trumpRed);

	Cards getCardThatIsChosenToPlay(int index);
	int getIndexOfCardThatIsChosenToPlay(std::string suit, std::string rank);
	void userChoosesCardToPlay(std::string chooseCardDependingOnsuit);
	std::string getChosenCardSuit();
	std::string getChosenCardRank();

	int numberOfASpecificSuitInHand(std::string suitName);

protected:
	std::vector<Cards> hand;
	bool hasJack;
	bool jackSuitColor;
	bool jackOfTheTrumpSuit;
	bool redTrump;
	std::string suitTrump;
	int numberOfRedCards;
	int numberOfBlackCards;

	std::string chosenSuit;
	std::string chosenRank;

	bool shouldThisTopCardBeTrump;
};

#endif // !EUCHRE_USER_H
