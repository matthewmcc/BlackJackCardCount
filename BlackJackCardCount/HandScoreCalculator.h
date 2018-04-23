#include "stdafx.h"
#include "CardDeck.h"

#include <list>
#include <map>

#pragma once
// Calculates the score of a Black Jack hand.
class HandScoreCalculator
{
public:
	HandScoreCalculator() {};
	~HandScoreCalculator() {};

	int calculateScore(std::list<Card> &hand);

	bool handIsSoft(std::list<Card> &hand);

	inline int getCardValue(Card &card) 
	{ 
		return BlackJack::CARD_RANK_TO_VALUE[card.Rank - 1]; 
	};

private:
	inline int reduceScoreByAces(int&, int&);

	inline int aceInHandCount(std::list<Card>&);

	inline int calculateHighAceScore(std::list<Card>&);
	inline int possibleAceReductions(int&, int&);
	inline bool isOver21(int &score);
};
