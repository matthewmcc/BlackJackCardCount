#include "BlackJackTableThreader.h"

#pragma once
// Runs a black jack simulation for each players hand outcome to find the best move...
// ...to make at each black jack state.
class BlackJackMoveFinder
{
public:
	BlackJackMoveFinder(int amountOfPacksInDeck, int amountOfPlayers);
	~BlackJackMoveFinder();

	void findMoves(int iterationsPerMove);

	void clearResults();

private:
	BlackJackTableThreader TableThreader;
	int IterationsPerMove;

	void getMovesForPlayerScore(bool, int);
};