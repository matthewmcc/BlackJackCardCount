#include "Dealer.h"
#include "Player.h"

#pragma once
// Calculates the results of played hands and stores the results by HandState
class OddsSamplerHandler
{
public:
	OddsSamplerHandler(Dealer &dealer, std::list<Player> &players);
	~OddsSamplerHandler();

	Dealer DealerResult;
	std::list<Player> PlayersResult;

	void getResults();
};

