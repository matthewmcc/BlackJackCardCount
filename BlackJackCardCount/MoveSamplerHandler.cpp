#include "stdafx.h"
#include "MoveSamplerHandler.h"
#include "BlackJackResultChecker.h"
#include "MoveSamplerResultStorage.h"

MoveSamplerHandler::MoveSamplerHandler(Dealer &dealer, std::list<Player> &players)
{
	DealerResult = dealer;
	PlayersResult = players;

	ResultStore = MoveSamplerResultStorage::getInstance();
};

MoveSamplerHandler::~MoveSamplerHandler()
{

};

void MoveSamplerHandler::getResults()
{
	BlackJackResultChecker resultChecker = BlackJackResultChecker(DealerResult);

	for (Player &player : PlayersResult)
	{
		resultChecker.addNextPlayer(player);
		double result = resultChecker.getBetMultiplier();

		while (player.hasHandStates())
		{
			HandState handState = player.popHandState();

			HandResult handResult = HandResult(handState);

			handResult.Result = result;
			handResult.PlayersMove = player.popMove();

			storeResults(handResult);
		}
	}

	ResultStore->handPlayed();
};

void MoveSamplerHandler::storeResults(HandResult &handResult)
{
	ResultStore->storeResult(handResult);
};