#include "stdafx.h"
#include "BlackJackWinOddsFinder.h"
#include "OddsFinderResultStorage.h"

#include <ctime>
#include <iostream>
#include <string>

BlackJackWinOddsFinder::BlackJackWinOddsFinder(int packsInDeck, int amountOfPlayers)
{
	Table = BlackJackTable(packsInDeck, amountOfPlayers);
}

BlackJackWinOddsFinder::~BlackJackWinOddsFinder()
{
}

void BlackJackWinOddsFinder::findOdds(int finderIterations) 
{
	// Temp //
	double start = clock();
	double stop, elapsedTime, percentComplete, estimatedTime;
	// Temp //

	for (int i = 0; i < finderIterations; i++)
	{
		Table.playRound();

		// Temp //
		if ((int)i % 1000 == 0)
		{
			stop = clock();
			elapsedTime = (stop - start) / (double)CLOCKS_PER_SEC;
			percentComplete = (i / (double)finderIterations) * 100.0;
			estimatedTime = ((100 / (percentComplete + 0.0000001)) * elapsedTime) - elapsedTime;

			std::cout << '\r' << "Percent complete: " << std::to_string(percentComplete) << "%"
				<< ", Estimated time till completion: " << (int)estimatedTime / 60 << " minutes, "
				<< (int)estimatedTime % 60 << " seconds";
		}
		// Temp //
	}


	OddsFinderResultStorage* storage = OddsFinderResultStorage::getInstance();
	storage->printResults();
};