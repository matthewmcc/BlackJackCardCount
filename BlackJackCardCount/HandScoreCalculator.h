#include "stdafx.h"
#include "CardDeck.h"
//#include "BlackJack.h"

#include <list>
#include <map>

#pragma once
class HandScoreCalculator
{
public:
	HandScoreCalculator() {};
	~HandScoreCalculator() {};

	int calculateScore(std::list<Card>&);

	bool handIsSoft(std::list<Card>&);

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

