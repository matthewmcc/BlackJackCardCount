#include "stdafx.h"
#include "MoveFinderResultHandler.h"
#include "BlackJackResultChecker.h"
#include "MoveFinderResultStorage.h"

MoveFinderResultHandler::MoveFinderResultHandler(Dealer &dealer, std::list<Player> &players)
{
	DealerResult = dealer;
	PlayersResult = players;

	ResultStore = MoveFinderResultStorage::getInstance();
};

MoveFinderResultHandler::~MoveFinderResultHandler()
{

};

void MoveFinderResultHandler::getResults()
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

void MoveFinderResultHandler::storeResults(HandResult &handResult)
{
	ResultStore->storeResult(handResult);
};