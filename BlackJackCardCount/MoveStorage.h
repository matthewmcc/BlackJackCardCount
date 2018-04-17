#include "stdafx.h"
#include "MoveSamplerResultStorage.h"
#include "LeastSquaresRegression.h"
//#include "BlackJack.h"

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
class MoveStorage
{
public:
	static MoveStorage* getInstance()
	{
		if (instance == 0)
			instance = new MoveStorage();

		return instance;
	};

	bool containsMove(HandState);

	char getMove(HandState, double);

	void addMoveFunction(HandState, MoveFunctions);

private:
	static MoveStorage* instance;

	std::map<HandState, MoveFunctions> MoveTable;

	MoveStorage();
	~MoveStorage();
};

