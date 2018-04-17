#include "BlackJackTable.h"

#include <list>
#include <thread>

#pragma once
class BlackJackTableThreader
{
public:
	BlackJackTableThreader(int amountOfPacksInDeck, int amountOfPlayers)
	{
		AmountOfPacksInDeck = amountOfPacksInDeck;
		AmountOfPlayers = amountOfPlayers;
	};
	BlackJackTableThreader() {};
	~BlackJackTableThreader();

	void runTableThreads(int, bool);

	void playRounds();

private:
	int AmountOfPacksInDeck;
	int AmountOfPlayers;
	int IterationsPerThread;
	int RequiredIterations;
	bool IsMoveFindingMode;

	double ThreadsStartTime;

	void printTimeEstimate();
};

