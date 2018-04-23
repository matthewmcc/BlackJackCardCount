#include "stdafx.h"
#include "OddsSamplerResultStorage.h"

#include <iostream>
#include <string>

OddsSamplerResultStorage* OddsSamplerResultStorage::instance = 0;

OddsSamplerResultStorage::OddsSamplerResultStorage()
{
	WinLossTally = 0.0;
	TotalPlayed = 0.0;
}

OddsSamplerResultStorage::~OddsSamplerResultStorage()
{
}


void OddsSamplerResultStorage::storeResult(int indexBeforeDeal, double betMultiplier)
{
	WriteMutex.lock();

	if (HandResultsByIndex.find(indexBeforeDeal) == HandResultsByIndex.end())
	{ 
		addNewIndexResults(indexBeforeDeal);
	}

	HandResultsByIndex[indexBeforeDeal].addResult(betMultiplier);

	WinLossTally += OUTCOME_VALUE[betMultiplier];
	TotalPlayed++;

	WriteMutex.unlock();
};

void OddsSamplerResultStorage::addNewIndexResults(int newIndex)
{
	IndexResults newIndexResults = IndexResults();
	HandResultsByIndex[newIndex] = newIndexResults;
};

void OddsSamplerResultStorage::printResults()
{
	std::cout << std::endl;

	std::map<double, double> totalPerBetMultiplier =
		{ { BlackJack::LOSS, 0 },{ BlackJack::PUSH, 0 },
		{ BlackJack::WIN, 0 },{ BlackJack::BLACK_JACK_WIN, 0 } };

	for (std::pair<int, IndexResults> indexHandResult : HandResultsByIndex)
	{
		double totalAtIndex = 0, winLossOdds = 0;

		for (std::pair<double, int> amount : indexHandResult.second.HandResults)
		{
			winLossOdds += OUTCOME_VALUE[amount.first] * amount.second;

			totalPerBetMultiplier[amount.first] += (double) amount.second;
			totalAtIndex += amount.second;
		}

		std::cout << std::endl 
			<< "Index: " << indexHandResult.first
			<< ", Loss percent: " << std::to_string((indexHandResult.second.HandResults[0.0] / totalAtIndex) * 100)
			<< ", Push percent: " << std::to_string((indexHandResult.second.HandResults[1.0] / totalAtIndex) * 100)
			<< ", Win percent: " << std::to_string((indexHandResult.second.HandResults[2.0] / totalAtIndex) * 100)
			<< ", Black Jack win percent: " << std::to_string((indexHandResult.second.HandResults[2.5] / totalAtIndex) * 100)
			<< ", Win odds: " << std::to_string((winLossOdds / totalAtIndex) * 100);
	}

	std::cout << std::endl << std::endl
		<< "Loss percent: " << (totalPerBetMultiplier[0.0] / TotalPlayed) * 100
		<< ", Push percent: " << (totalPerBetMultiplier[1.0] / TotalPlayed) * 100
		<< ", Win percent: " << (totalPerBetMultiplier[2.0] / TotalPlayed) * 100
		<< ", Black Jack win percent: " << (totalPerBetMultiplier[2.5] / TotalPlayed) * 100;

	std::cout << std::endl << std::endl
		<< "Win loss gain percentage: " << (WinLossTally / TotalPlayed) * 100 << "%" << std::endl
		<< "Total hands played: " << std::to_string(TotalPlayed) << std::endl;
};