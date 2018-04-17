#include "stdafx.h"
#include "BlackJackResultToCSV.h"
#include "LeastSquaresRegression.h"

#include <string>

BlackJackResultToCSV* BlackJackResultToCSV::instance = 0;

BlackJackResultToCSV::BlackJackResultToCSV()
{
	std::ofstream resultFile;
	resultFile.open(CSVFileName);
	resultFile.clear();

	resultFile << "Players Score, Dealers Card, Index, Players Move, HandResult" << std::endl;

	resultFile.close();
}

BlackJackResultToCSV::~BlackJackResultToCSV()
{
}

void BlackJackResultToCSV::writeToCSV(std::list<HandResult> results)
{
	std::ofstream resultFile;
	resultFile.open(CSVFileName, std::ios_base::app);

	for each (HandResult handResult in results)
	{
		resultFile << std::to_string(handResult.HandState.PlayersScore) << ", ";
		resultFile << std::to_string(handResult.HandState.DealersUpCardValue) << ", ";
		resultFile << std::to_string(handResult.HandState.Index) << ", ";
		resultFile << handResult.PlayersMove << ", ";
		resultFile << std::to_string(handResult.Result) << std::endl;
	}

	resultFile.close();
};

void BlackJackResultToCSV::writeToCSV(HandState state, RegressionLists hitLists, RegressionLists standLists)
{
	std::ofstream resultFile;
	std::string fileName = CSVFileDirectory +
		std::to_string(state.PlayersScore) + "," + std::to_string(state.DealersUpCardValue)+",";

	if (state.PlayersScoreIsSoft)
		fileName += "isSoft.csv";
	else
		fileName += "isHard.csv";

	resultFile.open(fileName, std::ios_base::app);

	resultFile << "Index, Result, Players move" << std::endl;

	std::list<double>::iterator xIterator = hitLists.X.begin();
	std::list<double>::iterator yIterator = hitLists.Y.begin();
	std::list<double>::iterator countsIterator = hitLists.Counts.begin();

	while (xIterator != hitLists.X.end())
	{
		for (int i = 0; i < *countsIterator; i++)
		{
			resultFile << *xIterator << ", " << *yIterator << ", " << 'H' << std::endl;
		}

		xIterator++; yIterator++; countsIterator++;
	}

	xIterator = standLists.X.begin();
	yIterator = standLists.Y.begin();
	countsIterator = standLists.Counts.begin();

	while (xIterator != standLists.X.end())
	{
		for (int i = 0; i < *countsIterator; i++)
		{
			resultFile << *xIterator << ", " << *yIterator << ", " << 'S' << std::endl;
		}

		xIterator++; yIterator++; countsIterator++;
	}

	resultFile.close();
}

