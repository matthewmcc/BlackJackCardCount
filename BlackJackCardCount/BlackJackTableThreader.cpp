#include "stdafx.h"
#include "BlackJackTableThreader.h"
#include "MoveSamplerResultStorage.h"

#include <windows.h>
#include <ctime>
#include <iostream>
#include <string>

BlackJackTableThreader::~BlackJackTableThreader()
{
}

void BlackJackTableThreader::runTableThreads(int requiredIterations, bool isMoveFindingMode)
{
	int maxThreads = (int)std::thread::hardware_concurrency() - 1;
	RequiredIterations = requiredIterations;
	IterationsPerThread = requiredIterations / maxThreads;
	IsMoveFindingMode = isMoveFindingMode;

	std::list<std::thread> tableThreads;

	ThreadsStartTime = clock();

	for (int i = 0; i < maxThreads; i++)
	{
		tableThreads.push_back(std::thread(&BlackJackTableThreader::playRounds, this));
	}

	printTimeEstimate();

	for (std::thread &tableThread : tableThreads)
	{
		tableThread.join();
	}
};

void BlackJackTableThreader::playRounds()
{
	BlackJackTable newTable = BlackJackTable(AmountOfPacksInDeck, AmountOfPlayers);
	if (IsMoveFindingMode)
	{
		newTable.setToMoveFindingMode();
	}

	for (int i = 0; i < IterationsPerThread; i++)
	{
		newTable.playRound();
	}
};

void BlackJackTableThreader::printTimeEstimate()
{
	double stop, elapsedTime, percentComplete, estimatedTime, handsPlayed;

	MoveSamplerResultStorage* resultHandler = MoveSamplerResultStorage::getInstance();

	handsPlayed = resultHandler->getHandsPlayed();

	while (handsPlayed < (RequiredIterations)-100)
	{
		stop = clock();
		elapsedTime = (stop - ThreadsStartTime) / (double)CLOCKS_PER_SEC;
		percentComplete = (handsPlayed / (double)RequiredIterations) * 100.0;
		estimatedTime = ((100 / (percentComplete + 0.0000001)) * elapsedTime) - elapsedTime;

		std::cout << '\r' << "Percent complete: " << std::to_string(percentComplete) << "%"
			<< ", Estimated time till completion: " << (int)estimatedTime / 60 << " minutes, "
			<< (int)estimatedTime % 60 << " seconds";

		Sleep(100);
		handsPlayed = resultHandler->getHandsPlayed();
	}
};