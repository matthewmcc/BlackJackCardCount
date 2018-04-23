#include "stdafx.h"
#include "MoveSamplerResultStorage.h"
#include "LeastSquaresRegression.h"

// Holds linear functions for hit and stand moves.
struct MoveFunctions {
	MoveFunctions(LinearFunction hitFunction, LinearFunction standFunction)
	{
		HitFunction = hitFunction;
		StandFunction = standFunction;
	};
	MoveFunctions() {};

	char getMoveByIndex(double index)
	{
		double hitValue = HitFunction.getYCoordinate(index);
		double standValue = StandFunction.getYCoordinate(index);

		return standValue > hitValue ? BlackJack::STAND : BlackJack::HIT;
	};

	LinearFunction HitFunction;
	LinearFunction StandFunction;
};

#pragma once
// Stores MoveFunctions by HandState to calculate moves by index.
class MoveStorage
{
public:
	static MoveStorage* getInstance()
	{
		if (instance == 0)
			instance = new MoveStorage();

		return instance;
	};

	bool containsMove(HandState state);

	char getMove(HandState &state, double index);

	void addMoveFunction(HandState state, MoveFunctions function);

private:
	static MoveStorage* instance;

	std::map<HandState, MoveFunctions> MoveTable;

	MoveStorage();
	~MoveStorage();

	void makeHandStateSortable(HandState&);
};

