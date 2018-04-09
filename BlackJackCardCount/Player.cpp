#include "stdafx.h"

#include "Player.h"
#include "HandScoreCalculator.h"

Player::Player()
{
	CardsInHand;// = std::list<Card>();

	MovesMade;// = std::stack<char>();
	PlayersStates;// = std::stack<HandState>();

	ScoreCalculator = HandScoreCalculator();
}

Player::~Player()
{
}

void Player::addCardToHand(Card &newCard)
{
	CardsInHand.push_back(newCard);
};

void Player::hit(Card &newCard)
{
	addCardToHand(newCard);

	MovesMade.push(HIT_MARKER);
};

void Player::stand()
{
	MovesMade.push(STAND_MARKER);
};

void Player::resetHand() 
{
	CardsInHand.clear();
	MovesMade = std::stack<char>();
	PlayersStates = std::stack<HandState>();
};

HandState& Player::getHandState(double index)
{
	createHandState(index);

	return PlayersStates.top();
};

void Player::createHandState(double index)
{
	HandState newState;

	newState.Index = index;
	newState.PlayersScore = getHandScore();
	newState.PlayersScoreIsSoft = ScoreCalculator.handIsSoft(CardsInHand);
	newState.DealersUpCardValue = DealersCurrentUpCardValue;

	PlayersStates.push(newState);
}

int Player::getHandScore()
{
	return ScoreCalculator.calculateScore(CardsInHand);
};