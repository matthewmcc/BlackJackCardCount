#include "stdafx.h"
#include "BlackJackResultToCSV.h"
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

