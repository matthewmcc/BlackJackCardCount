#include "stdafx.h"
#include "Dealer.h"
#include "HandScoreCalculator.h"

Dealer::Dealer()
{
	ScoreCalculator = HandScoreCalculator();
}

Dealer::~Dealer()
{
}

void Dealer::addCardToHand(Card &newCard)
{
	CardsInHand.push_back(newCard);
};

void Dealer::addUpCard(Card &newCard)
{
	CardsInHand.push_back(newCard);
	UpCard = newCard;
};

void Dealer::addDownCard(Card &newCard)
{
	CardsInHand.push_back(newCard);
	DownCard = newCard;
};

bool Dealer::dealerHits()
{
	int handsScore = getHandScore();

	if (!handAtMaxSize())
	{
		if (handsScore <= BlackJack::DEALER_HARD_HIT_MAX)
			return true;

		if (handsScore == BlackJack::DEALER_SOFT_HIT_MAX && handIsSoft())
			return true;
	}

	return false;
};

bool Dealer::handAtMaxSize()
{
	return ((int) CardsInHand.size()) >= BlackJack::MAX_HAND_SIZE;
};

bool Dealer::handIsSoft()
{
	return ScoreCalculator.handIsSoft(CardsInHand);
};

int Dealer::getHandScore()
{
	return ScoreCalculator.calculateScore(CardsInHand);
};

void Dealer::resetHand()
{
	CardsInHand.clear();
};