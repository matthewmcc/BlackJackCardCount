// BlackJackCardCount.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "MoveSamplerResultStorage.h"
#include "ResultsToMoves.h"
#include "BlackJackMoveFinder.h"
#include "BlackJackWinOddsFinder.h"

//#include "BlackJack.h"

#include <time.h>
#include <iostream>
#include <string>
#include <ctime>

int main()
{
	srand((unsigned)time(NULL));

	BlackJack::RESHUFFLE_RATIO = .75;

	BlackJackMoveFinder moveFinder = 
		BlackJackMoveFinder(BlackJack::PACKS_IN_DECK, BlackJack::PLAYERS_AT_TABLE);
	moveFinder.findMoves(1000000);

	BlackJack::RESHUFFLE_RATIO = .75;

	BlackJackWinOddsFinder oddsFinder = 
		BlackJackWinOddsFinder(BlackJack::PACKS_IN_DECK, BlackJack::PLAYERS_AT_TABLE);
	oddsFinder.findOdds(5000000);

	return 0;
}