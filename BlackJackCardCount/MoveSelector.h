#include "MoveSamplerHandler.h"
#include "MoveStorage.h"

#pragma once
// Checks if a MoveFunction for a HandState has been calculated yet. Returns the best move...
// ...for the HandState and Index if it has or a random move if it hasn't.
class MoveSelector
{
public:
	MoveSelector()
	{
		Moves = MoveStorage::getInstance();
		Results = MoveSamplerResultStorage::getInstance();
	};

	~MoveSelector();

	char move(HandState &handState, double index);

private:
	MoveStorage* Moves;
	MoveSamplerResultStorage* Results;

	char randomMove();
};

