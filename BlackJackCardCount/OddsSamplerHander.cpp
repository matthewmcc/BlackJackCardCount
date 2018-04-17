#include "stdafx.h"
#include "OddsSamplerHandler.h"
#include "BlackJackResultChecker.h"
#include "OddsSamplerResultStorage.h"

OddsSamplerHandler::OddsSamplerHandler(Dealer &dealer, std::list<Player> &players)
{
	DealerResult = dealer;
	PlayersResult = players;
}

OddsSamplerHandler::~OddsSamplerHandler()
{
}

void OddsSamplerHandler::getResults()
{
	BlackJackResultChecker resultChecker = BlackJackResultChecker(DealerResult);
	OddsSamplerResultStorage* resultStorage = OddsSamplerResultStorage::getInstance();

	for (Player &player : PlayersResult)
	{
		resultChecker.addNextPlayer(player);
		resultStorage->storeResult(resultChecker.getBetMultiplier());
	}
};

