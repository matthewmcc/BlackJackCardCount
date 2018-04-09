#include "MoveFinderResultStorage.h"
#include "LeastSquaresRegression.h"
#include "MoveStorage.h"

#pragma once
class ResultsToMoves
{
public:
	ResultsToMoves()
	{
		MoveStore = MoveStorage::getInstance();
	};

	~ResultsToMoves();

	void convertResultsToMoves();

private:
	MoveStorage* MoveStore;
	std::map<double, double> OutcomeValue = { { 0, -1 },{ 1, 1 },{ 2, 2 },{ 2.5, 2.5 } };

	void divideResultsByHandState(std::map<HandState, HandStateResults>);

	void getRegressionFunctions(std::map<HandState, HandStateResults>);

	RegressionLists createHitRegressionLists(std::map<HandState, HandStateResults> &singleStateResult);
	RegressionLists createStandRegressionLists(std::map<HandState, HandStateResults> &singleStateResult);

	void storeMoveFunctions(HandState, MoveFunctions);


	void printNewFunction(HandState, MoveFunctions, int);
};
