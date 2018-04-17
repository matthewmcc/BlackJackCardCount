#include "MoveSamplerHandler.h"
#include "MoveStorage.h"

#pragma once
class MoveSelector
{
public:
	MoveSelector()
	{
		Moves = MoveStorage::getInstance();
		Results = MoveSamplerResultStorage::getInstance();
	};

	~MoveSelector();

	char move(HandState&, double);

private:
	MoveStorage* Moves;
	MoveSamplerResultStorage* Results;

	char randomMove();
};

