#include "BlackJackTable.h"
#include "BlackJackTableThreader.h"

#pragma once
// Simulates Black Jack using the Moves given in each state from MoveSelector and stores...
// ...the results in OddsSamplerResultStorage.
class BlackJackWinOddsFinder
{
public:
	BlackJackWinOddsFinder(int packsInDeck, int amountOfPlayers);
	~BlackJackWinOddsFinder();

	BlackJackTableThreader TableThreader;
	int IterationsPerMove;

	void findOdds(int finderIterations);
};

