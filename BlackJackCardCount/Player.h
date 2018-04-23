#include "stdafx.h"
#include "CardDeck.h"
#include "MoveSamplerResultStorage.h"
#include "HandScoreCalculator.h"

#include <list>
#include <stack>

#pragma once
// Simulates a Black Jack player storing the states of the players hand as rounds...
// ...are played.
class Player
{
public:
	Player();
	~Player();

	void addCardToHand(Card &newCard);

	void hit(Card &newCard);
	void stand();

	std::list<Card>& getHand() { return CardsInHand; };
	inline int getHandScore();

	inline bool handAtMaxSize() 
	{ 
		return  (int)CardsInHand.size() >= BlackJack::MAX_HAND_SIZE; 
	};

	bool hasHandStates() { return PlayersStates.size() != 0; };
	HandState& getHandState(double index);

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

	void setIndexBeforeDeal(double index) { IndexBeforeDeal = round(index); };
	int getIndexBeforeDeal() { return IndexBeforeDeal; };

	void resetHand();

private:
	HandScoreCalculator ScoreCalculator;

	std::list<Card> CardsInHand;
	int DealersCurrentUpCardValue;

	std::stack<char> MovesMade;

	std::stack<HandState> PlayersStates;

	int IndexBeforeDeal;

	void createHandState(double);
};

