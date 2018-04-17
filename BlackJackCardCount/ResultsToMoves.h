#include "stdafx.h"
#include "MoveSamplerResultStorage.h"
#include "LeastSquaresRegression.h"
#include "MoveStorage.h"
//#include "BlackJack.h"

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
	std::map<double, double> OUTCOME_VALUE = 
		{ {BlackJack::LOSS, -1}, { BlackJack::PUSH, 1 },
		{ BlackJack::WIN, 2 }, { BlackJack::BLACK_JACK_WIN, 2.5 } };

	void divideResultsByHandState(std::map<HandState, HandStateResults>);

	void getRegressionFunctions(std::map<HandState, HandStateResults>);

	RegressionLists createHitRegressionLists(std::map<HandState, HandStateResults> &singleStateResult);
	RegressionLists createStandRegressionLists(std::map<HandState, HandStateResults> &singleStateResult);

	void storeMoveFunctions(HandState, MoveFunctions);


	void printNewFunction(HandState, MoveFunctions, int);

	void printListIndex(std::map<HandState, HandStateResults>);

	void checkBetChangeIndex(MoveFunctions);
};
