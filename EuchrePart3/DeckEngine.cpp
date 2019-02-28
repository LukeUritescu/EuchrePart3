#include "pch.h"
#include "DeckEngine.h"

void DeckEngine::createDeck()
{
	deckOfCards = new std::vector<Cards>;
	drawnCards = new std::vector <Cards>;
	for (int n = 0; n < 4; n++) {
		for (int i = 1; i < 7 + 1; i++)
		{
			if (n == 0) {
				suit = "Hearts";
				red = true;
			}
			else if (n == 1) {
				suit = "Diamonds";
				red = true;
			}
			else if (n == 2) {
				suit = "Clubs";
				red = false;
			}
			else if (n == 3) {
				suit = "Spades";
				red = false;
			}
			switch (i) {
			case 1:
				value = 7;
				rank = "Ace";
				break;
			case 2:
				value = 1;
				rank = "Eight";
				break;
			case 3:
				value = 2;
				rank = "Nine";
				break;
			case 4:
				value = 3;
				rank = "Ten";
				break;
			case 5:
				value = 4;
				rank = "Jack";
				break;
			case 6:
				value = 5;
				rank = "Queen";
				break;
			case 7:
				value = 6;
				rank = "King";
				break;
			}
			Cards card(value, rank, suit, red);
			index++;
			deckOfCards->push_back(card);
		}
	}



}

void DeckEngine::shuffle()
{
	std::random_shuffle(deckOfCards->begin(), deckOfCards->end());
}


void DeckEngine::printDeck()
{
	for (std::vector<Cards>::iterator it = deckOfCards->begin(); it != deckOfCards->end(); ++it)
	{
		std::cout << it->getSuit() << " " << it->getRank() << " " << it->getValue() << std::endl;
		std::cout << "===================" << std::endl;
	}
	std::cout << index << std::endl;
}

int DeckEngine::getIndex()
{
	return index;
}

Cards DeckEngine::drawCard()
{
	drawnCards->push_back(deckOfCards->back());
	deckOfCards->pop_back();
	index--;
	return drawnCards->back();
}

std::string DeckEngine::trumpCard()
{
	return deckOfCards->back().getSuit();
}

bool DeckEngine::showTrumpSuit()
{
	return deckOfCards->back().getRed();
}

bool DeckEngine::emptyDeck()
{
	if (index == 0)
	{
		//From my research http://www.cplusplus.com/reference/vector/vector/clear/ 
		//http://www.cplusplus.com/reference/utility/swap/?kw=swap
		// It seems swap is a better function to use instead of clear for what I am trying to do.
		std::vector<Cards>().swap(*deckOfCards);
		return true;
	}
	else {
		return false;
	}
}

void DeckEngine::deleteVectors()
{
	delete deckOfCards;
	delete drawnCards;
}



