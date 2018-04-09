#include "stdafx.h"
#include "ResultsToConsole.h"

#include <iostream>
#include <string>

ResultsToConsole::ResultsToConsole()
{
}

ResultsToConsole::~ResultsToConsole()
{
}     

void ResultsToConsole::PrintResults(std::map<HandState, HandStateResults> resultsCounter)
{
	for each (std::pair<HandState, HandStateResults> result in resultsCounter)
	{
		double totalHitsPlayed = 0.0, totalStandsPlayed = 0.0, winOdds = 0.0;

		for each (std::pair<double, int> incrementedResults in result.second.HitResults)
			totalHitsPlayed += incrementedResults.second;

		for each (std::pair<double, int> incrementedResults in result.second.StandResults)
			totalStandsPlayed += incrementedResults.second;

		if (totalStandsPlayed < 100 || totalHitsPlayed < 100)
			continue;

		std::cout << std::endl << std::to_string(result.first.PlayersScore) << ", "
			<< std::to_string(result.first.DealersUpCardValue) << ", "
			<< std::to_string(result.first.Index) << std::endl;

		std::cout << " Win loss percent: " << CalculateWinOdds(result.second.HitResults) << "%"
			<< ", Win odds: " << (result.second.HitResults[2.0] / totalHitsPlayed) * 100 << "%"
			<< ", Loss odds: " << (result.second.HitResults[0.0] / totalHitsPlayed) * 100 << "%"
			<< ", Stand odds: " << (result.second.HitResults[1.0] / totalHitsPlayed) * 100 << "%" << std::endl;

		std::cout << " Win loss percent: " << CalculateWinOdds(result.second.StandResults) << "%"
			<< ", Win odds: " << (result.second.StandResults[2.0] / totalStandsPlayed) * 100 << "%"
			<< ", Loss odds: " << (result.second.StandResults[0.0] / totalStandsPlayed) * 100 << "%"
			<< ", Stand odds: " << (result.second.StandResults[1.0] / totalStandsPlayed) * 100 << "%" << std::endl;


		std::cout << std::endl;
	}


};

double ResultsToConsole::CalculateWinOdds(std::map<double, int> specificHandOutcomeResult)
{
	std::map<double, double> outcomeValue = { {0, -1}, {1, 1}, {2, 2}, {2.5, 2.5} };

	double totalPlayed = 0.0, winLossOdds = 0.0;

	for each (std::pair<double, int> incrementedResults in specificHandOutcomeResult)
	{
		totalPlayed += incrementedResults.second;
		winLossOdds += outcomeValue[incrementedResults.first] * incrementedResults.second;
	}

	return (winLossOdds / totalPlayed) * 100;
};
