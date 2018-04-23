#include "CardDeck.h"
#include "Dealer.h"
#include "Player.h"
#include "MoveSamplerResultStorage.h"

#include <list>

#pragma once
// Converts Dealer and Player states to HandState HandResults pairs and stores pairs...
// ...that HandStates match the currently calculated moves.
class MoveSamplerHandler
{
public:
	MoveSamplerHandler(Dealer &dealer, std::list<Player> &players);
	~MoveSamplerHandler();

	void getResults();

private:
	Dealer DealerResult;
	std::list<Player> PlayersResult;

	MoveSamplerResultStorage* ResultStore;

	void storeResults(HandResult&);
};

