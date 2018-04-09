#include "stdafx.h"

#include "MoveSelector.h"

MoveSelector::~MoveSelector()
{
}

char MoveSelector::move(HandState &handState, double index)
{
	if (handState.PlayersScore > 20)
	{
		return 'S';
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
		return 'H';
	else
		return 'S';
};