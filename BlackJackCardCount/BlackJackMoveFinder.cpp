#include "stdafx.h"
#include "BlackJackMoveFinder.h"
#include "ResultsToMoves.h"
#include "MoveSamplerResultStorage.h"

#include <iostream>
#include <ctime>
#include <string>

BlackJackMoveFinder::BlackJackMoveFinder(int amountOfPacksInDeck, int amountOfPlayers)
{
	TableThreader = BlackJackTableThreader(amountOfPacksInDeck, amountOfPlayers);
}

BlackJackMoveFinder::~BlackJackMoveFinder()
{
}

void BlackJackMoveFinder::findMoves(int iterationsPerMove)
{
	IterationsPerMove = iterationsPerMove;

	for (int playerHardScore = 20; playerHardScore >= 4; playerHardScore--)
	{
		getMovesForPlayerScore(true, playerHardScore);
	}

	for (int playerSoftScore = 20; playerSoftScore >= 13; playerSoftScore--)
	{
		getMovesForPlayerScore(false, playerSoftScore);
	}
};

void BlackJackMoveFinder::getMovesForPlayerScore(bool hardMoves, int playerScore)
{
	MoveSamplerResultStorage* resultStore = MoveSamplerResultStorage::getInstance();
	resultStore->updateScoreToStore(hardMoves, playerScore);

	TableThreader.runTableThreads(IterationsPerMove, true);

	ResultsToMoves moveAdder = ResultsToMoves();
	moveAdder.convertResultsToMoves();

	clearResults();
};

void BlackJackMoveFinder::clearResults()
{
	MoveSamplerResultStorage* resultStore = MoveSamplerResultStorage::getInstance();
	resultStore->clearResults();
}