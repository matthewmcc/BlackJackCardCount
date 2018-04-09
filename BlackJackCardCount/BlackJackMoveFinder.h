#include "BlackJackTableThreader.h"

#pragma once
class BlackJackMoveFinder
{
public:
	BlackJackMoveFinder(int, int);
	~BlackJackMoveFinder();

	void findMoves(int);

	void clearResults();

private:
	BlackJackTableThreader TableThreader;
	int IterationsPerMove;

	void getMovesForPlayerScore(bool, int);
};

