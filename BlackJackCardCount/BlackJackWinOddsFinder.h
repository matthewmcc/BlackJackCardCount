#include "BlackJackTable.h"

#pragma once
class BlackJackWinOddsFinder
{
public:
	BlackJackWinOddsFinder(int, int);
	~BlackJackWinOddsFinder();

	BlackJackTable Table;
	int IterationsPerMove;

	void findOdds(int);
};

