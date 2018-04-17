#include "stdafx.h"
#include "CardDeck.h"
#include "MoveSamplerResultStorage.h"
#include "HandScoreCalculator.h"
//#include "BlackJack.h"

#include <list>
#include <stack>

#pragma once
class Player
{
public:
	Player();
	~Player();

	void addCardToHand(Card&);

	void hit(Card&);
	void stand();

	std::list<Card>& getHand() { return CardsInHand; };
	inline int getHandScore();

	inline bool handAtMaxSize() 
	{ 
		return  (int)CardsInHand.size() >= BlackJack::MAX_HAND_SIZE; 
	};

	bool hasHandStates() { return PlayersStates.size() != 0; };
	HandState& getHandState(double);

	void setDealersUpCard(Card &upCard) 
	{ 
		DealersCurrentUpCardValue = ScoreCalculator.getCardValue(upCard); 
	};

	char popMove() 
	{   
		char move = MovesMade.top();
		MovesMade.pop(); 

		return move;
	};

	HandState& popHandState()
	{
		HandState state = PlayersStates.top();
		PlayersStates.pop();

		return state;
	};

	void resetHand();

private:
	HandScoreCalculator ScoreCalculator;

	std::list<Card> CardsInHand;
	int DealersCurrentUpCardValue;

	std::stack<char> MovesMade;

	std::stack<HandState> PlayersStates;

	void createHandState(double);
};

