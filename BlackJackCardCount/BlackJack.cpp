#include "BlackJack.h"

namespace BlackJack
{
	///			Black jack constants		///
	char STAND = 'S';
	char HIT = 'H';

	int MAX_SCORE = 21;
	int MAX_HAND_SIZE = 5;

	int BUST_ACE_SCORE_REDUCTION = 10;

	double PUSH = 1;
	double BLACK_JACK_WIN = 2.5;
	double WIN = 2;
	double LOSS = 0;

	// Gives the value of each cards by rank from Ace to King
	int CARD_RANK_TO_VALUE[] = { { 11 },{ 2 },{ 3 },{ 4 },
	{ 5 },{ 6 },{ 7 },{ 8 },{ 9 },{ 10 },{ 10 },{ 10 },{ 10 } };
	///			Black jack constants ^^		///

	///			Black jack parameters		///
	int PLAYERS_AT_TABLE = 5;
	int PACKS_IN_DECK = 6;

	int DEALER_HARD_HIT_MAX = 16;
	int DEALER_SOFT_HIT_MAX = 16;

	// Ratio of deck that must be played before theres a reshuffle
	double RESHUFFLE_RATIO = 0.25;

	// Minimum amount of results to not be considered an outlier
	int MIN_RESULT_AMONUT = 10;
	///			Black jack parameters ^^	///
};