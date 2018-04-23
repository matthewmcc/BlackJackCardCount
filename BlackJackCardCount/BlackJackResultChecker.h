#include "stdafx.h"
#include "Dealer.h"
#include "Player.h"
#include "HandScoreCalculator.h"

#include <map>

#pragma once
// Used to find the bet multiplier given a Dealer and Player with complete hands
class BlackJackResultChecker
{
public:
	BlackJackResultChecker(Dealer &tableDealer);
	~BlackJackResultChecker();

	void addNextPlayer(Player &player);

	double getBetMultiplier();

private:
	int DealersScore;

	int PlayersScore;
	bool PlayerHasBlackJack;

	inline bool isPlayerBust();
	inline bool isDealerBust();

	inline bool isWin();
	inline bool isPush();

	inline void calculateDealersScore(Dealer&);
	inline void calculatePlayersScore(Player&);

	inline bool playerBlackJack(std::list<Card>&);
};

