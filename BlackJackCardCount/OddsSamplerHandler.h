#include "Dealer.h"
#include "Player.h"

#pragma once
class OddsSamplerHandler
{
public:
	OddsSamplerHandler(Dealer&, std::list<Player>&);
	~OddsSamplerHandler();

	Dealer DealerResult;
	std::list<Player> PlayersResult;

	void getResults();
};

