#include "CardDeck.h"
#include "HandScoreCalculator.h"

#include <list>

#pragma once
class Dealer
{
public:
	Dealer();
	~Dealer();

	void addCardToHand(Card &newCard);
	// Adds the dealers card thats visable to the players to the dealers hand
	void addUpCard(Card &newCard);
	// Adds the dealers card thats not visable to the players to the dealers hand
	void addDownCard(Card& newCard);

	std::list<Card>& getHand() { return CardsInHand; };
	Card& getUpCard() { return UpCard; };
	Card& getDownCard() { return DownCard; };

	int getHandScore();

	bool dealerHits();

	void resetHand();

private:
	int DEALER_HARD_HIT_MAX = 16;
	int DEALER_SOFT_HIT_MAX = 17;
	int MAX_HAND_SIZE = 5;

	std::list<Card> CardsInHand;
	Card UpCard;
	Card DownCard;

	HandScoreCalculator ScoreCalculator;

	bool handIsSoft();
	bool handAtMaxSize();
};

