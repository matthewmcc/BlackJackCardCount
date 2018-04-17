#include "stdafx.h"
#include "HandScoreCalculator.h"

// Removes 10 from each ace while dealers score is bust
int HandScoreCalculator::calculateScore(std::list<Card> &hand)
{
	int score = calculateHighAceScore(hand);
	int amountOfAces = aceInHandCount(hand);

	return reduceScoreByAces(score, amountOfAces);
};

int HandScoreCalculator::reduceScoreByAces(int &score, int &amountOfAces)
{
	for (int i = 0; i < amountOfAces && isOver21(score); i++)
		score -= BlackJack::BUST_ACE_SCORE_REDUCTION;

	return score;
};

bool HandScoreCalculator::handIsSoft(std::list<Card> &hand)
{
	int aceCount = aceInHandCount(hand);

	if (aceCount == 0)
		return false;

	int score = calculateHighAceScore(hand);
	int amountOfAces = aceInHandCount(hand);

	int timesAceReduced = possibleAceReductions(score, amountOfAces);

	if (timesAceReduced == amountOfAces)
		return false;
	
	return true;
};

int HandScoreCalculator::aceInHandCount(std::list<Card> &hand)
{
	int aceCount = 0;

	for each (Card card in hand)
		if (card.Rank == 1)
			aceCount++;

	return aceCount;
};

int HandScoreCalculator::calculateHighAceScore(std::list<Card> &hand)
{
	int score = 0;

	for each (Card card in hand)
		score += BlackJack::CARD_RANK_TO_VALUE[card.Rank - 1];

	return score;
};

int HandScoreCalculator::possibleAceReductions(int &score, int &amountOfAces)
{
	int amountReduced = 0;

	for (int i = 0; i < amountOfAces && isOver21(score); i++)
	{
		score -= BlackJack::BUST_ACE_SCORE_REDUCTION;
		amountReduced++;
	}

	return amountReduced;
};

bool HandScoreCalculator::isOver21(int &score)
{
	return score > BlackJack::MAX_SCORE;
};
