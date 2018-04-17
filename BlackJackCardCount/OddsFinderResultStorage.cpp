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

void OddsSamplerResultStorage::storeResult(double betMultiplier)
{
	BetMultiplerResults[betMultiplier]++;

	WinLossTally += betMultiplier == 0 ? -1 : 0;
	WinLossTally += betMultiplier == 1 ? 0 : 0;
	WinLossTally += betMultiplier == 2 ? 1 : 0;
	WinLossTally += betMultiplier == 2.5 ? 1.5 : 0;

	TotalPlayed++;
};

void OddsSamplerResultStorage::printResults()
{
	std::cout << std::endl << std::endl
		<< "Loss percent: " << (BetMultiplerResults[0.0] / TotalPlayed) * 100
		<< ", Push percent: " << (BetMultiplerResults[1.0] / TotalPlayed) * 100
		<< ", Win percent: " << (BetMultiplerResults[2.0] / TotalPlayed) * 100
		<< ", Black Jack win percent: " << (BetMultiplerResults[2.5] / TotalPlayed) * 100 << std::endl

		<< "Win loss gain percentage: " << (WinLossTally / TotalPlayed) * 100 << "%" << std::endl
		<< "Total hands played: " << std::to_string(TotalPlayed) << std::endl;
};