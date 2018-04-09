#include "stdafx.h"
#include "MoveStorage.h"

MoveStorage* MoveStorage::instance = 0;

MoveStorage::MoveStorage()
{
}

MoveStorage::~MoveStorage()
{
}

bool MoveStorage::containsMove(HandState state)
{
	// Sets index to 0 because its value is no longer needed.
	state.Index = 0;

	return (MoveTable.count(state) != 0);
};

char MoveStorage::getMove(HandState state, double index) 
{ 
	// Sets index to 0 because its value is no longer needed.
	state.Index = 0;

	MoveFunctions moveFunction = MoveTable[state];

	return moveFunction.getMoveByIndex(index);
};

void MoveStorage::addMoveFunction(HandState state, MoveFunctions function)
{
	// Sets index to 0 because its value is no longer needed.
	state.Index = 0;

	std::pair<HandState, MoveFunctions> newMove = std::pair<HandState, MoveFunctions>(state, function);
	MoveTable.insert(newMove);
};