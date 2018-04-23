#include "BlackJackTable.h"

#include <list>
#include <thread>

#pragma once
// Runs Black Jack table objects on multiple threads until a the passed amount of iterations...
// ...are met.
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

	void runTableThreads(int requiredIterations, bool isMoveFindingMode);

private:
	int AmountOfPacksInDeck;
	int AmountOfPlayers;
	int IterationsPerThread;
	int RequiredIterations;
	bool IsMoveFindingMode;

	double ThreadsStartTime;

	void playRounds();

	void printTimeEstimate();

	double getHandsPlayed();
};

