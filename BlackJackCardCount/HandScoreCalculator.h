#include "CardDeck.h"

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

	inline int getCardValue(Card &card) { return CARD_RANK_TO_VALUE[card.Rank - 1]; };

private:
	// Gives the value of each cards by rank from Ace to King
	std::vector<int> CARD_RANK_TO_VALUE = { {11 },{2 },{ 3 },{ 4 },
		{ 5 },{ 6 },{ 7 },{ 8 },{ 9 },{ 10 },{ 10 },{ 10 },{ 10 } };

	int MAX_HAND_SCORE = 21;
	int BUST_ACE_SCORE_REDUCTION = 10;
	int ACE_RANK_VALUE = 1; 

	inline int reduceScoreByAces(int&, int&);

	inline int aceInHandCount(std::list<Card>&);

	inline int calculateHighAceScore(std::list<Card>&);
	inline int possibleAceReductions(int&, int&);
	inline bool isOver21(int &score);
};

