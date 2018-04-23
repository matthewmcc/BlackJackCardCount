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
	makeHandStateSortable(state);

	return (MoveTable.count(state) != 0);
};

char MoveStorage::getMove(HandState &state, double index) 
{ 
	makeHandStateSortable(state);

	MoveFunctions moveFunction = MoveTable[state];

	return moveFunction.getMoveByIndex(index);
};

void MoveStorage::addMoveFunction(HandState state, MoveFunctions function)
{
	makeHandStateSortable(state);

	std::pair<HandState, MoveFunctions> newMove = std::pair<HandState, MoveFunctions>(state, function);
	MoveTable.insert(newMove);
};

void MoveStorage::makeHandStateSortable(HandState &state)
{
	// Sets index to 0 because its value is no longer needed for sorting.
	state.Index = 0;
};