#include "stdafx.h"
#include "BlackJackResultChecker.h"

BlackJackResultChecker::BlackJackResultChecker(Dealer &tableDealer)
{
	calculateDealersScore(tableDealer);
}


BlackJackResultChecker::~BlackJackResultChecker()
{
}

void BlackJackResultChecker::addNextPlayer(Player &player)
{
	calculatePlayersScore(player);
};

// Returns the value the players bet should multplied by depending if they win.
// Loss = 0, Push = 1, Win = 2, Black jack = 2.5.
double BlackJackResultChecker::getBetMultiplier()
{
	if (isPlayerBust())
		return LOSS_MULTIPLIER;

	if (isDealerBust())
		if (PlayerHasBlackJack)
			return BLACK_JACK_MULTIPLIER;
		else
			return WIN_MULTIPLIER;

	if (isPush())
		return PUSH_MULTIPLIER;

	if (isWin())
	{
		if (PlayerHasBlackJack)
			return BLACK_JACK_MULTIPLIER;
		else
			return WIN_MULTIPLIER;
	}
	else
		return LOSS_MULTIPLIER;
};

bool BlackJackResultChecker::isPlayerBust()
{
	return PlayersScore > MAX_SCORE;

};

bool BlackJackResultChecker::isDealerBust()
{
	return DealersScore > MAX_SCORE;
};

// When the player and dealer are not bust and have an equal score.
bool BlackJackResultChecker::isPush()
{
	return DealersScore == PlayersScore;
};

// A push where the player and dealer have an equal score is returned as true.
bool BlackJackResultChecker::isWin()
{
	return PlayersScore >= DealersScore;
};

void BlackJackResultChecker::calculateDealersScore(Dealer &dealer)
{
	DealersScore = dealer.getHandScore();
};

void BlackJackResultChecker::calculatePlayersScore(Player &player)
{
	PlayersScore = player.getHandScore();

	PlayerHasBlackJack = playerBlackJack(player.getHand());
};

bool BlackJackResultChecker::playerBlackJack(std::list<Card> &hand)
{
	return (PlayersScore == 21 && hand.size() == 2);
};
