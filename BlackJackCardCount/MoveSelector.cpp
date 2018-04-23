#include "stdafx.h"

#include "MoveSelector.h"

MoveSelector::~MoveSelector()
{
}

char MoveSelector::move(HandState &handState, double index)
{
	if (handState.PlayersScore > 20)
	{
		return BlackJack::STAND;
	}

	if (Moves->containsMove(handState))
	{
		return Moves->getMove(handState, index);
	}

	return randomMove();
};

char MoveSelector::randomMove()
{
	if (rand() % 2)
		return BlackJack::HIT;
	else
		return BlackJack::STAND;
};