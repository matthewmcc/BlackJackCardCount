#include "stdafx.h"
#include "MoveFinderResultStorage.h"
#include "ResultsToMoves.h"
#include "LeastSquaresRegression.h"

#include <iostream>
#include <string>
#include <map>
#include <list>

ResultsToMoves::~ResultsToMoves()
{
}

void ResultsToMoves::convertResultsToMoves()
{
	MoveFinderResultStorage* resultStorage = MoveFinderResultStorage::getInstance();

	std::map<HandState, HandStateResults> ResultsCounters = resultStorage->getResults();
	divideResultsByHandState(ResultsCounters);
}

void ResultsToMoves::divideResultsByHandState(std::map<HandState, HandStateResults> resultsCounters)
{
	HandState stateToMatch = (*resultsCounters.begin()).first;
	std::map<HandState, HandStateResults> singleStateResult = std::map<HandState, HandStateResults>();

	for (std::pair<HandState, HandStateResults> resultState : resultsCounters)
	{
		if (resultState.first.stateEqualButIndex(stateToMatch))
		{
			singleStateResult.insert(resultState);
		}
		else
		{
			getRegressionFunctions(singleStateResult);

			stateToMatch = resultState.first;
			singleStateResult = std::map<HandState, HandStateResults>();
		}
	}

	getRegressionFunctions(singleStateResult);
};

void ResultsToMoves::getRegressionFunctions(std::map<HandState, HandStateResults> singleStateResult)
{
	RegressionLists hitOddsTotalsWeightsLists = createHitRegressionLists(singleStateResult);

	LeastSquaresRegression hitRegression = LeastSquaresRegression(hitOddsTotalsWeightsLists);
	CartesianLinearFunction hitFunction = hitRegression.calculateLine();


	RegressionLists standOddsTotalsWeightsLists = createStandRegressionLists(singleStateResult);

	LeastSquaresRegression standRegression = LeastSquaresRegression(standOddsTotalsWeightsLists);
	CartesianLinearFunction standFunction = standRegression.calculateLine();


	MoveFunctions moveFunctions = MoveFunctions(hitFunction, standFunction);

	HandState functionsHandState = (*singleStateResult.begin()).first;
	storeMoveFunctions(functionsHandState, moveFunctions);

	printNewFunction(functionsHandState, moveFunctions, hitRegression.NumberOfPoints + standRegression.NumberOfPoints);
};


RegressionLists ResultsToMoves::createHitRegressionLists(std::map<HandState, HandStateResults> &singleStateResult)
{
	RegressionLists dataLists = RegressionLists();

	for (std::pair<HandState, HandStateResults> resultState : singleStateResult)
	{
		double totalPlayed = 0.0, winLossOdd = 0.0;

		for each (std::pair<double, int> incrementedResults in resultState.second.HitResults)
		{
			totalPlayed += incrementedResults.second;
			winLossOdd += OutcomeValue[incrementedResults.first] * incrementedResults.second;
		}

		if (totalPlayed != 0)
		{
			double y = (winLossOdd / totalPlayed) * 100;
			dataLists.addDataInstance(resultState.first.Index, y, (int) totalPlayed);
		}
	}

	return dataLists;
};

RegressionLists ResultsToMoves::createStandRegressionLists(std::map<HandState, HandStateResults> &singleStateResult)
{
	RegressionLists dataLists = RegressionLists();

	for (std::pair<HandState, HandStateResults> resultState : singleStateResult)
	{
		double totalPlayed = 0.0, winLossOdd = 0.0;

		for each (std::pair<double, int> incrementedResults in resultState.second.StandResults)
		{
			totalPlayed += incrementedResults.second;
			winLossOdd += OutcomeValue[incrementedResults.first] * incrementedResults.second;
		}

		if (totalPlayed != 0)
		{
			double y = (winLossOdd /  totalPlayed) * 100.0;
			dataLists.addDataInstance(resultState.first.Index, y, (int) totalPlayed);
		}
	}

	return dataLists;
};

void ResultsToMoves::storeMoveFunctions(HandState state, MoveFunctions function)
{
	MoveStore->addMoveFunction(state, function);
};


void ResultsToMoves::printNewFunction(HandState state, MoveFunctions functions, int numberOfPoints)
{
	std::cout << '\r' << "Players move: " << state.PlayersScore;

	if (state.PlayersScoreIsSoft)
		std::cout << ", soft score, ";
	else
		std::cout << ", hard score, ";

	std::cout << "Dealers card: " << state.DealersUpCardValue
		<< ", Number Sampled: " << numberOfPoints << std::endl;

	std::cout << "Hit function: y = " << functions.HitFunction.Slope << "x + " 
		<< functions.HitFunction.YIntercept << std::endl;

	std::cout << "Stand function: y = " << functions.StandFunction.Slope << "x + "
		<< functions.StandFunction.YIntercept << std::endl << std::endl;
};
