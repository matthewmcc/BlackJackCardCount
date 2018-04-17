//#include "BlackJack.h"

#include <unordered_map>
#include <list>
#include <map>

enum Suit
{
	Heart = 1,
	Diamond = 2,
	Club = 3,
	Spade = 4
};

enum Rank
{
	Ace = 1, Two = 2, Three = 3, Four = 4, Five = 5, 
	Six = 6, Seven = 7, Eight = 8, Nine = 9, Ten = 10,
	Jack = 11, Queen = 12, King = 13
};

struct Card {
	int Suit;
	int Rank;

	Card() {};
	Card(int suit, int rank) {
		Suit = suit;
		Rank = rank;
	};

	bool operator==(const Card& a) const
	{
		return (Suit == a.Suit && Rank == a.Rank);
	}
};

template <>
struct std::hash<Card>
{
	std::size_t operator()(const Card& card) const
	{
		return std::hash<int>()(card.Suit)
			^ (std::hash<int>()(card.Rank)  << 1);
	};
};

#pragma once
class CardDeck
{
public:
	CardDeck(int amountOfPacks);
	CardDeck() {};
	~CardDeck();

	int deckSize() { return DeckSize; };
	Card drawCard();
	Card drawDealerHiddenCard();

	double getCurrentRealCount();

	void updateIndex(Card&);

	void reshuffleDeck();

private:
	double AmountOfPacks;
	double CurrentIndex;
	std::unordered_map<Card, int> Deck = std::unordered_map<Card, int>();
	int DeckSize;

	double CARD_DECK_SIZE = 52;

	int RANKS[13] = { Ace, Two, Three, Four, Five, Six, Seven, 
		Eight, Nine, Ten, Jack, Queen, King };
	int RANKS_SIZE = 13;

	// Values of cards replaced with the values they get within a Hi-Lo card counting system.
	std::map<int, double> HI_LO_VALUES = { { Ace, -1 },{ Two, 1 },{ Three, 1 },{ Four, 1 },{ Five, 1 },
		{ Six, 1 },{ Seven, 0 },{ Eight, 0 },{ Nine, 0 },{ Ten, -1 },{ Jack, -1 },{ Queen, -1 },{ King, -1 } };

	int SUITS[4] = { Heart, Diamond, Club, Spade };
	int SUITS_SIZE = 4;

	void createDeck(int);

	bool reshuffleRequried();

	Card& removeRandomCard();
	Card& randomCard();
};
