#include "stdafx.h"
#include "Dealer.h"
#include "Player.h"
#include "HandScoreCalculator.h"
//#include "BlackJack.h"

#include <map>

#pragma once
class BlackJackResultChecker
{
public:
	BlackJackResultChecker(Dealer&);
	~BlackJackResultChecker();

	void addNextPlayer(Player&);

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

