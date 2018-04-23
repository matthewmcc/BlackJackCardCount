#include "stdafx.h"
#include "MoveSamplerResultStorage.h"
#include "LeastSquaresRegression.h"
#include "MoveStorage.h"

#pragma once
// Converts results stored in MoveSamplerResultStorage to MoveFunctions and stores them...
// ...in MoveStorage while printing the moves calculated to be made for each HandState.
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
	std::map<double, double> OUTCOME_VALUE = 
		{ {BlackJack::LOSS, -1}, { BlackJack::PUSH, 0 },
		{ BlackJack::WIN, 1 }, { BlackJack::BLACK_JACK_WIN, 1.5 } };

	void divideResultsByHandState(std::map<HandState, HandStateResults>);

	void getRegressionFunctions(HandState, std::map<int, HandStateResults>);

	RegressionLists createHitRegressionLists(std::map<int, HandStateResults>&);
	LinearFunction createHitLinearFunction(std::map<int, HandStateResults>&);

	RegressionLists createStandRegressionLists(std::map<int, HandStateResults>&);
	LinearFunction createStandLinearFunction(std::map<int, HandStateResults>&);

	bool isNotOutlier(std::map<double, int>&);
	void addNewMoveResults(RegressionLists&, std::map<double, int>&, double);

	void storeMoveFunctions(HandState, MoveFunctions);


	void printNewFunction(HandState, MoveFunctions);

	void printListIndex(std::map<HandState, HandStateResults>);

	void checkBetChangeIndex(MoveFunctions);
};
