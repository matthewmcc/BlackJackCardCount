#include "MoveFinderResultHandler.h"
#include "MoveStorage.h"

#pragma once
class MoveSelector
{
public:
	MoveSelector()
	{
		Moves = MoveStorage::getInstance();
		Results = MoveFinderResultStorage::getInstance();
	};

	~MoveSelector();

	char move(HandState&, double);

private:
	MoveStorage* Moves;
	MoveFinderResultStorage* Results;

	char randomMove();
};

