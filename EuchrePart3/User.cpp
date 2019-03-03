#include "pch.h"
#include "User.h"

///Create a deicision tree for if they do not lke the top drawn card.
///If they don't have a jack check for aces, if nothing there check for king, and queen
void User::acquireCard(Cards card)
{
	hand.push_back(card);
}

void User::dealDropsWorstCard(std::string trumpSuit)
{
	int i = 0;
	Cards tempCard;
	for (std::vector<Cards>::iterator it = hand.begin(); it != hand.end(); ++it)
	{

		//This is to check the values 
		
		i++;
	}
}

void User::showHand(std::string name)
{
	for (std::vector<Cards>::iterator it = hand.begin(); it != hand.end(); ++it)
	{
		std::cout << name << " " << it->getSuit() << " " << it->getRank()/* << " " << it->getValue()*/ << std::endl;
	}
}

int User::numberOfSpadesInHand()
{
	int  i = 0;
	for (std::vector<Cards>::iterator it = hand.begin(); it != hand.end(); ++it)
	{
		if (it->getSuit() == "Spades") {
			i++;
		}

	}
	return i;
}

int User::numberOfClubsInHand()
{
	int  i = 0;
	for (std::vector<Cards>::iterator it = hand.begin(); it != hand.end(); ++it)
	{
		if (it->getSuit() == "Clubs") {
			i++;
		}

	}
	return i;
}

int User::numberOfHeartsInHand()
{
	int  i = 0;
	for (std::vector<Cards>::iterator it = hand.begin(); it != hand.end(); ++it)
	{
		if (it->getSuit() == "Hearts") {
			i++;
		}

	}
	return i;
}

int User::numberOfDiamondsInHand()
{
	int  i = 0;
	for (std::vector<Cards>::iterator it = hand.begin(); it != hand.end(); ++it)
	{
		if (it->getSuit() == "Diamonds") {
			i++;
		}

	}
	return i;
}

void User::whenTheDealerDoesNotLikeTrumpCard(int spades, int clubs, int diamonds, int hearts)
{
	if (spades + clubs > diamonds + hearts) {
		if (spades > clubs) {
			suitTrump = "Spades";
			redTrump = false;
		}
		else {
			suitTrump = "Clubs";
			redTrump = false;
		}
	}
	else {
		if (diamonds > hearts) {
			suitTrump = "Diamonds";
			redTrump = true;
		}
		else {
			suitTrump = "Hearts";
			redTrump = true;
		}
	}

}

std::string User::getSuitTrump()
{
	return suitTrump;
}

bool User::getRed()
{
	return redTrump;
}

void User::decisionOnTrumpCard(std::string suit, bool red)
{
	///check deicions on trump card
	if (findJackInHand()) {
		if (hasJackSameSuitColor(suit, red)) {
			if (hasJackTrumpSuit(suit)) {
				shouldThisTopCardBeTrump = true;
			}

			else {
				shouldThisTopCardBeTrump = true;
			}
		}
		else
			shouldThisTopCardBeTrump = false;
	}
	else
		shouldThisTopCardBeTrump = false;



}

bool User::getShouldThisTopCardBeTrump()
{
	return shouldThisTopCardBeTrump;
}


bool User::findJackInHand()
{
	hasJack = false;
	for (std::vector<Cards>::iterator it = hand.begin(); it != hand.end(); ++it)
	{
		if (it->getRank() == "Jack") {
			hasJack = true;
		}

	}
	return hasJack;

}

bool User::hasJackSameSuitColor(std::string suit, bool red)
{
	for (std::vector<Cards>::iterator it = hand.begin(); it != hand.end(); ++it)
	{
		if (it->getRed() == red && it->getRank() == "Jack") {
			jackSuitColor = true;
		}
	}
	return jackSuitColor;
}

bool User::hasJackTrumpSuit(std::string suit)
{
	//this will check if the user has the highest card for the round. if the do then they will choose to make the top card on the deck the trump for the turn
	for (std::vector<Cards>::iterator it = hand.begin(); it != hand.end(); ++it)
	{
		if (it->getSuit() == suit && it->getRank() == "Jack") {
			jackOfTheTrumpSuit = true;
		}
	}
	return jackOfTheTrumpSuit;
}

