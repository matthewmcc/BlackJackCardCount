// BlackJackCardCount.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "MoveFinderResultStorage.h"
#include "ResultsToConsole.h"
#include "ResultsToMoves.h"
#include "BlackJackMoveFinder.h"
#include "BlackJackWinOddsFinder.h"

#include <time.h>
#include <iostream>
#include <string>
#include <ctime>

int main()
{
	srand((unsigned)time(NULL));

	int PacksInDeck = 6;
	int PlayersAtTable = 5;

	BlackJackMoveFinder moveFinder = BlackJackMoveFinder(PacksInDeck, PlayersAtTable);
	moveFinder.findMoves(500000);

	BlackJackWinOddsFinder oddsFinder = BlackJackWinOddsFinder(PacksInDeck, PlayersAtTable);
	oddsFinder.findOdds(1000000);

	return 0;
}