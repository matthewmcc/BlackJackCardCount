#include "CardDeck.h"
#include "Dealer.h"
#include "Player.h"
#include "MoveFinderResultStorage.h"

#include <list>

#pragma once
class MoveFinderResultHandler
{
public:
	MoveFinderResultHandler(Dealer &dealer, std::list<Player> &players);
	~MoveFinderResultHandler();

	void getResults();

private:
	Dealer DealerResult;
	std::list<Player> PlayersResult;

	MoveFinderResultStorage* ResultStore;

	void storeResults(HandResult&);
};

