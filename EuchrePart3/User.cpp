#include "pch.h"
#include "User.h"

///Create a deicision tree for if they do not lke the top drawn card.
///If they don't have a jack check for aces, if nothing there check for king, and queen
void User::acquireCard(Cards card)
{
	hand.push_back(card);
}

void User::dealDropsWorstCard(bool trumpRed)
{
	int i = 0;
	int tempCardIndex = 0;
	int tempCardValue = 10;
	for (std::vector<Cards>::iterator it = hand.begin(); it != hand.end(); ++it)
	{
		//This is to check the values 
		if (tempCardValue > it->getValue() && it->getRank() != "Jack") {
			tempCardValue = it->getValue();
			tempCardIndex = i;
		}
		i++;
	}
	hand.erase(hand.begin() + tempCardIndex);
}

void User::showHand(std::string name)
{
	for (std::vector<Cards>::iterator it = hand.begin(); it != hand.end(); ++it)
	{
		std::cout << name << " " << it->getSuit() << " " << it->getRank()/* << " " << it->getValue()*/ << std::endl;
	}
}

int User::getIndexOfCardThatIsChosenToPlay(std::string suit, std::string rank)
{
	int i = 0;
	int index = 0;
	for (std::vector<Cards>::iterator it = hand.begin(); it != hand.end(); ++it)
	{
		if (it->getSuit() == suit && it->getRank() == rank)
			index = i;
		i++;
	}
	return index;
}
Cards User::getCardThatIsChosenToPlay(int index)
{
	//chose .at because from what I googled it seems to be safer than using []
	return hand.at(index);
}


void User::userChoosesCardToPlay(std::string chooseCardDependingOnsuit)
{
	int tempValue = 0;
	for (std::vector<Cards>::iterator it = hand.begin(); it != hand.end(); ++it)
	{
		if (chooseCardDependingOnsuit == it->getSuit()) {
			chosenSuit = it->getSuit();
			chosenRank = it->getRank();
			tempValue = it->getValue();
			if (it->getRank() == "Jack") {
				chosenRank = it->getRank();
				tempValue = 9;//because the hghest value is 7 normally. so 9 s the right bower and jack of same color suit will be 8 as the left bower
			}
			else if(tempValue < it->getValue()) //this is to check if there are multiple cards of the same suit in user's hand that they pick the highest value one
				chosenRank = it->getRank();
		}
		else {
			//This is to check the values 
			if (tempValue < it->getValue()) {
				chosenSuit = it->getSuit();
				chosenRank = it->getRank();
				tempValue = it->getValue();
			}
		}
	}
}
std::string User::getChosenCardSuit()
{
	return chosenSuit;
}
std::string User::getChosenCardRank()
{
	return chosenRank;
}
//Can condense this into one function with a parameter where the suit name is the given one. 
int User::numberOfASpecificSuitInHand(std::string suitName)
{
	int  i = 0;
	for (std::vector<Cards>::iterator it = hand.begin(); it != hand.end(); ++it)
	{
		if (it->getSuit() == suitName) {
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



