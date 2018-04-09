#include "stdafx.h"
#include "CardDeck.h"

CardDeck::CardDeck(int amountOfPacks)
{
	DeckSize = amountOfPacks * (int) CARD_DECK_SIZE;
	AmountOfPacks = (double) amountOfPacks;
	CurrentIndex = 0.0;

	createDeck((int)AmountOfPacks);
}

CardDeck::~CardDeck()
{
}

void CardDeck::createDeck(int amountOfPacks) {
	for (int suit : SUITS)
	{
		for (int rank : RANKS)
		{
			Deck[Card(suit, rank)] = amountOfPacks;
		}
	}
};

void CardDeck::reshuffleDeck()
{
	if (DeckSize < (CARD_DECK_SIZE * AmountOfPacks) - ReshuffleAmount)
	{
		// Returns all the values of how many cards in the hash to Amount of packs
		for (auto deckIterator = Deck.begin(); deckIterator != Deck.end(); ++deckIterator)
		{
			deckIterator->second = (int) AmountOfPacks;
		}

		DeckSize = (int) AmountOfPacks * CARD_DECK_SIZE;
		CurrentIndex = 0.0;
	}
};

// Removes a random card from the Deck, adds it to PlayedCards and returns it.
Card CardDeck::drawCard()
{
	Card drawnCard = removeRandomCard();

	updateIndex(drawnCard);

	return drawnCard;
};

Card CardDeck::drawDealerHiddenCard()
{
	Card drawnCard = removeRandomCard();

	return drawnCard;
};

Card& CardDeck::removeRandomCard()
{
	Card drawnCard = randomCard();


	while (Deck[drawnCard] == 0)
	{
		drawnCard = randomCard();
	}

	Deck[drawnCard]--;
	DeckSize--;

	return drawnCard;
};

Card& CardDeck::randomCard()
{
	int randomSuit = SUITS[rand() % SUITS_SIZE];
	int randomRank = RANKS[rand() % RANKS_SIZE];

	return Card(randomSuit, randomRank);
};

// Divides the CurrentIndex by the amount of packs left to give the Real count;
double CardDeck::getCurrentRealCount()
{
	double packsLeft = (((double)deckSize()) / CARD_DECK_SIZE) / AmountOfPacks;
	return CurrentIndex / packsLeft;
};

void CardDeck::updateIndex(Card& cardRemoved)
{
	CurrentIndex += HI_LO_VALUES[cardRemoved.Rank];
};

