#include "stdafx.h"
#include "MoveSamplerResultStorage.h"
#include "ResultsToMoves.h"
#include "LeastSquaresRegression.h"
#include "GradientDescent.h"
//#include "BlackJack.h"
#include "BlackJackResultToCSV.h"

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

	//LeastSquaresRegression hitRegression = LeastSquaresRegression(hitOddsTotalsWeightsLists);
	GradientDescent hitRegression = GradientDescent(hitOddsTotalsWeightsLists);
	LinearFunction hitFunction = hitRegression.calculateLine();


	RegressionLists standOddsTotalsWeightsLists = createStandRegressionLists(singleStateResult);

	//LeastSquaresRegression standRegression = LeastSquaresRegression(standOddsTotalsWeightsLists);
	GradientDescent standRegression = GradientDescent(standOddsTotalsWeightsLists);
	LinearFunction standFunction = standRegression.calculateLine();


	MoveFunctions moveFunctions = MoveFunctions(hitFunction, standFunction);

	HandState functionsHandState = (*singleStateResult.begin()).first;
	storeMoveFunctions(functionsHandState, moveFunctions);

	printNewFunction(functionsHandState, moveFunctions, 
		(int) (hitRegression.NumberOfPoints + standRegression.NumberOfPoints));

	//printListIndex(singleStateResult);


	//BlackJackResultToCSV* toCSV = BlackJackResultToCSV::getInstance();
	//toCSV->writeToCSV(functionsHandState, hitOddsTotalsWeightsLists, standOddsTotalsWeightsLists);
};


RegressionLists ResultsToMoves::createHitRegressionLists(std::map<HandState, HandStateResults> &singleStateResult)
{
	RegressionLists dataLists = RegressionLists();

	for (std::pair<HandState, HandStateResults> resultState : singleStateResult)
	{
		double totalPlayed = 0.0;

		for each (std::pair<double, int> incrementedResults in resultState.second.HitResults)
			totalPlayed += incrementedResults.second;

		if (totalPlayed > 5)
		{
			for each (std::pair<double, int> incrementedResults in resultState.second.HitResults)
			{
				if (incrementedResults.second > 0)
				{
					if (resultState.first.Index > 1000 || resultState.first.Index < -1000)
					{
						std::cout << std::endl << "Hit index error: " << resultState.first.Index
							<< ", Total played: " << totalPlayed << ", Count: " << incrementedResults.second << std::endl;

					}
					else
					{

						dataLists.addDataInstance(resultState.first.Index,
							OUTCOME_VALUE[incrementedResults.first], incrementedResults.second);
					}
				}
			}
		}
	}

	return dataLists;
};

RegressionLists ResultsToMoves::createStandRegressionLists(std::map<HandState, HandStateResults> &singleStateResult)
{
	RegressionLists dataLists = RegressionLists();

	for (std::pair<HandState, HandStateResults> resultState : singleStateResult)
	{
		double totalPlayed = 0.0;

		for each (std::pair<double, int> incrementedResults in resultState.second.StandResults)
			totalPlayed += incrementedResults.second;

		if (totalPlayed > 5)
		{
			for each (std::pair<double, int> incrementedResults in resultState.second.StandResults)
			{
				if (incrementedResults.second > 0)
				{
					if (resultState.first.Index > 1000 || resultState.first.Index < -1000)
					{
						std::cout << std::endl << "Stand index error: " << resultState.first.Index
							<< ", Total played: " << totalPlayed << ", Count: " << incrementedResults.second << std::endl;
					}
					else
					{

						dataLists.addDataInstance(resultState.first.Index,
							OUTCOME_VALUE[incrementedResults.first], incrementedResults.second);
					}
				}
			}
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
	std::cout << '\r' << "Players score: " << state.PlayersScore;

	if (state.PlayersScoreIsSoft)
		std::cout << ", soft score, ";
	else
		std::cout << ", hard score, ";

	std::cout << "Dealers card value: " << state.DealersUpCardValue
		<< ", Number Sampled: " << numberOfPoints << std::endl;

	std::cout << "Hit function: y = " << functions.HitFunction.Slope << "x + " 
		<< functions.HitFunction.YIntercept << std::endl;

	std::cout << "Stand function: y = " << functions.StandFunction.Slope << "x + "
		<< functions.StandFunction.YIntercept << std::endl;

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
