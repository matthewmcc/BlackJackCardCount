#include "stdafx.h"
#include "OddsFinderResultStorage.h"

#include <iostream>
#include <string>

OddsFinderResultStorage* OddsFinderResultStorage::instance = 0;

OddsFinderResultStorage::OddsFinderResultStorage()
{
	WinLossTally = 0.0;
	TotalPlayed = 0.0;
}

OddsFinderResultStorage::~OddsFinderResultStorage()
{
}

void OddsFinderResultStorage::storeResult(double betMultiplier)
{
	BetMultiplerResults[betMultiplier]++;
	WinLossTally += betMultiplier;
	TotalPlayed++;
};

void OddsFinderResultStorage::printResults()
{
	std::cout << std::endl << std::endl
		<< "Loss percent: " << (BetMultiplerResults[0.0] / TotalPlayed) * 100
		<< ", Stand percent: " << (BetMultiplerResults[1.0] / TotalPlayed) * 100
		<< ", Win percent: " << (BetMultiplerResults[2.0] / TotalPlayed) * 100
		<< ", Black Jack win percent: " << (BetMultiplerResults[2.5] / TotalPlayed) * 100 << std::endl

		<< "Win loss gain percentage: " << (WinLossTally / TotalPlayed) * 100 << "%" << std::endl
		<< "Total hands played: " << std::to_string(TotalPlayed) << std::endl;
};