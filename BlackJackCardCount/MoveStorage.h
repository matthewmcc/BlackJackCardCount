#include "MoveFinderResultStorage.h"
#include "LeastSquaresRegression.h"

struct MoveFunctions {
	MoveFunctions(CartesianLinearFunction hitFunction, CartesianLinearFunction standFunction)
	{
		HitFunction = hitFunction;
		StandFunction = standFunction;
	};
	MoveFunctions() {};

	char getMoveByIndex(double index)
	{
		double hitValue = HitFunction.getYCoordinate(index);
		double standValue = StandFunction.getYCoordinate(index);

		return standValue > hitValue ? 'S' : 'H';
	};

	CartesianLinearFunction HitFunction;
	CartesianLinearFunction StandFunction;
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

