#include "Dealer.h"
#include "Player.h"

#pragma once
class OddsFinderResultHander
{
public:
	OddsFinderResultHander(Dealer&, std::list<Player>&);
	~OddsFinderResultHander();

	Dealer DealerResult;
	std::list<Player> PlayersResult;

	void getResults();
};

