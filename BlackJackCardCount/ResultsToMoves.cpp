#include "stdafx.h"
#include "MoveSamplerResultStorage.h"
#include "ResultsToMoves.h"
#include "LeastSquaresRegression.h"
#include "GradientDescent.h"

#include <iostream>
#include <string>
#include <map>
#include <list>

ResultsToMoves::~ResultsToMoves()
{
}

void ResultsToMoves::convertResultsToMoves()
{
	MoveSamplerResultStorage* resultStorage = MoveSamplerResultStorage::getInstance();

	std::map<HandState, HandStateResults> ResultsCounters = resultStorage->getResults();
	divideResultsByHandState(ResultsCounters);
}

void ResultsToMoves::divideResultsByHandState(std::map<HandState, HandStateResults> resultsCounters)
{
	HandState stateToMatch = (*resultsCounters.begin()).first;
	std::map<int, HandStateResults> singleStateResult;

	for (std::pair<HandState, HandStateResults> resultState : resultsCounters)
	{
		if (resultState.first.stateEqualButIndex(stateToMatch))
		{
			singleStateResult[resultState.first.Index] = resultState.second;
		}
		else
		{
			getRegressionFunctions(stateToMatch, singleStateResult);

			stateToMatch = resultState.first;
			singleStateResult.clear();
		}
	}

	getRegressionFunctions(stateToMatch, singleStateResult);
};

void ResultsToMoves::getRegressionFunctions(HandState handState, 
	std::map<int, HandStateResults> singleStateResult)
{
	LinearFunction hitFunction = createHitLinearFunction(singleStateResult);
	LinearFunction standFunction = createStandLinearFunction(singleStateResult);

	MoveFunctions moveFunctions = MoveFunctions(hitFunction, standFunction);
	storeMoveFunctions(handState, moveFunctions);

	printNewFunction(handState, moveFunctions);

	//printListIndex(singleStateResult);
};

LinearFunction ResultsToMoves::createHitLinearFunction(std::map<int, HandStateResults> &singleStateResults)
{
	RegressionLists hitOddsTotalsWeightsLists = createHitRegressionLists(singleStateResults);

	LeastSquaresRegression hitRegression = LeastSquaresRegression(hitOddsTotalsWeightsLists);
	return hitRegression.calculateLine();
};

RegressionLists ResultsToMoves::createHitRegressionLists(std::map<int, HandStateResults> &singleStateResult)
{
	RegressionLists dataLists = RegressionLists();

	for (std::pair<int, HandStateResults> resultState : singleStateResult)
	{
		if (isNotOutlier(resultState.second.HitResults))
		{
			addNewMoveResults(dataLists, resultState.second.HitResults,
				resultState.first);
		}
	}

	return dataLists;
};

LinearFunction ResultsToMoves::createStandLinearFunction(std::map<int, HandStateResults> &singleStateResults)
{
	RegressionLists standOddsTotalsWeightsLists = createStandRegressionLists(singleStateResults);

	LeastSquaresRegression standRegression = LeastSquaresRegression(standOddsTotalsWeightsLists);
	return standRegression.calculateLine();
};

RegressionLists ResultsToMoves::createStandRegressionLists(std::map<int, HandStateResults> &singleStateResult)
{
	RegressionLists dataLists = RegressionLists();

	for (std::pair<int, HandStateResults> resultState : singleStateResult)
	{
		if (isNotOutlier(resultState.second.StandResults))
		{
			addNewMoveResults(dataLists, resultState.second.StandResults,
				resultState.first);
		}
	}

	return dataLists;
};

bool ResultsToMoves::isNotOutlier(std::map<double, int> &moveResults)
{
	double totalPlayed = 0.0;

	for each (std::pair<double, int> incrementedResults in moveResults)
		totalPlayed += incrementedResults.second;

	return totalPlayed > BlackJack::MIN_RESULT_AMONUT;
};

void ResultsToMoves::addNewMoveResults(RegressionLists &dataLists, std::map<double, int> &moveResults,
	double index)
{
	for each (std::pair<double, int> incrementedResults in moveResults)
	{
		if (incrementedResults.second > 0)
		{
			dataLists.addDataInstance(index,
				OUTCOME_VALUE[incrementedResults.first], incrementedResults.second);
		}
	}
};

void ResultsToMoves::storeMoveFunctions(HandState state, MoveFunctions function)
{
	MoveStore->addMoveFunction(state, function);
};


void ResultsToMoves::printNewFunction(HandState state, MoveFunctions functions)
{
	MoveSamplerResultStorage* resultStorage = MoveSamplerResultStorage::getInstance();

	std::cout << '\r' << "Players score: " << state.PlayersScore;

	if (state.PlayersScoreIsSoft)
		std::cout << ", soft score, ";
	else
		std::cout << ", hard score, ";

	std::cout << "Dealers card value: " << state.DealersUpCardValue << std::endl;

	//std::cout << "Hit function: y = " << functions.HitFunction.Slope << "x + " 
	//	<< functions.HitFunction.YIntercept << std::endl;

	//std::cout << "Stand function: y = " << functions.StandFunction.Slope << "x + "
	//	<< functions.StandFunction.YIntercept << std::endl;

	checkBetChangeIndex(functions);

	std::cout << std::endl;
};

void ResultsToMoves::printListIndex(std::map<HandState, HandStateResults> singleStateResult)
{
	std::cout << "============== HIT ===============" << std::endl;

	for (std::pair<HandState, HandStateResults> resultState : singleStateResult)
	{
		double hitTotalPlayed = 0.0;

		for each (std::pair<double, int> incrementedResults in resultState.second.HitResults)
			hitTotalPlayed += incrementedResults.second;

		if (hitTotalPlayed > 100)
		{
			std::cout << "Index: " << resultState.first.Index <<
				"\tLoss %: " << std::to_string((resultState.second.HitResults[0] / hitTotalPlayed) * 100) <<
				", Push %: " << std::to_string((resultState.second.HitResults[1] / hitTotalPlayed) * 100) <<
				", Win %: " << std::to_string((resultState.second.HitResults[2] / hitTotalPlayed) * 100) <<
				", Black Jack Win %: " << std::to_string((resultState.second.HitResults[2.5] / hitTotalPlayed) * 100) <<
				", Sampled: " << hitTotalPlayed << std::endl;
		}
	}

	std::cout << std::endl;
	std::cout << "============== STAND ===============" << std::endl;

	for (std::pair<HandState, HandStateResults> resultState : singleStateResult)
	{
		double standTotalPlayed = 0.0;

		for each (std::pair<double, int> incrementedResults in resultState.second.StandResults)
			standTotalPlayed += incrementedResults.second;

		if (standTotalPlayed > 100)
		{
			std::cout << "Index: " << resultState.first.Index <<
				"\tLoss %: " << std::to_string((resultState.second.StandResults[0] / standTotalPlayed) * 100) <<
				", Push %: " << std::to_string((resultState.second.StandResults[1] / standTotalPlayed) * 100) <<
				", Win %: " << std::to_string((resultState.second.StandResults[2] / standTotalPlayed) * 100) <<
				", Black Jack Win %: " << std::to_string((resultState.second.StandResults[2.5] / standTotalPlayed) * 100) <<
				", Sampled: " << standTotalPlayed << std::endl;
		}
	}

	std::cout << "============== END ===============" << std::endl << std::endl;
}

void ResultsToMoves::checkBetChangeIndex(MoveFunctions functions)
{
	char move = functions.getMoveByIndex(-25);
	bool change = false;

	for (int i = -24; i < 25; i++)
	{
		if (functions.getMoveByIndex(i) != move)
		{
			if (move == BlackJack::STAND)
				std::cout << "Change occured at: " << i << ", to hit " << std::endl;
			else
				std::cout << "Change occured at: " << i << ", to stand " << std::endl;

			change = true;
			break;
		}
	}

	if (change == false)
	{
		if (move == BlackJack::STAND)
			std::cout << "No change always stand." << std::endl;
		else
			std::cout << "No change always hit." << std::endl;
	}
};
