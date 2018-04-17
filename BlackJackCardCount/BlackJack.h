#ifndef BLACKJACK_H
#define BLACKJACK_H

namespace BlackJack
{
	///			Black jack constants		///
	extern char STAND;
	extern char HIT;

	extern int MAX_SCORE;
	extern int MAX_HAND_SIZE;

	extern int BUST_ACE_SCORE_REDUCTION;

	extern double PUSH;
	extern double BLACK_JACK_WIN;
	extern double WIN;
	extern double LOSS;

	// Gives the value of each cards by rank from Ace to King
	extern int CARD_RANK_TO_VALUE[];
	///			Black jack constants ^^		///

	///			Black jack parameters		///
	extern int PLAYERS_AT_TABLE;
	extern int PACKS_IN_DECK;

	extern int DEALER_HARD_HIT_MAX;
	extern int DEALER_SOFT_HIT_MAX;

	// Ratio of deck that must be played before theres a reshuffle
	extern double RESHUFFLE_RATIO;
	///			Black jack parameters ^^	///
};

#endif  BLACKJACK_H