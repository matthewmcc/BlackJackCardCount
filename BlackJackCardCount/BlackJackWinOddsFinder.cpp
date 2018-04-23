#include "stdafx.h"
#include "BlackJackWinOddsFinder.h"
#include "OddsSamplerResultStorage.h"

#include <ctime>
#include <iostream>
#include <string>

BlackJackWinOddsFinder::BlackJackWinOddsFinder(int packsInDeck, int amountOfPlayers)
{
	TableThreader = BlackJackTableThreader(packsInDeck, amountOfPlayers);
}

BlackJackWinOddsFinder::~BlackJackWinOddsFinder()
{
}

void BlackJackWinOddsFinder::findOdds(int finderIterations) 
{
	TableThreader.runTableThreads(finderIterations, false);

	OddsSamplerResultStorage* storage = OddsSamplerResultStorage::getInstance();
	storage->printResults();
};