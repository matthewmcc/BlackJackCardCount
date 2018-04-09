#include "Dealer.h"
#include "Player.h"
#include "HandScoreCalculator.h"

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
	const int MAX_SCORE = 21;

	const double PUSH_MULTIPLIER = 1;
	const double BLACK_JACK_MULTIPLIER = 2.5;
	const double WIN_MULTIPLIER = 2;
	const double LOSS_MULTIPLIER = 0;

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

