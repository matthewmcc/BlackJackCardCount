#include "stdafx.h"
#include "OddsFinderResultHander.h"
#include "BlackJackResultChecker.h"
#include "OddsFinderResultStorage.h"

OddsFinderResultHander::OddsFinderResultHander(Dealer &dealer, std::list<Player> &players)
{
	DealerResult = dealer;
	PlayersResult = players;
}

OddsFinderResultHander::~OddsFinderResultHander()
{
}

void OddsFinderResultHander::getResults()
{
	BlackJackResultChecker resultChecker = BlackJackResultChecker(DealerResult);
	OddsFinderResultStorage* resultStorage = OddsFinderResultStorage::getInstance();

	for (Player &player : PlayersResult)
	{
		resultChecker.addNextPlayer(player);
		resultStorage->storeResult(resultChecker.getBetMultiplier());
	}
};

