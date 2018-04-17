#include "stdafx.h"
#include "BlackJackTable.h"
#include "BlackJackResultChecker.h"
#include "CardDeck.h"
#include "MoveSamplerHandler.h"
#include "MoveSelector.h"
#include "OddsSamplerHandler.h"

BlackJackTable::BlackJackTable(int amountOfPacksInDeck, int amountOfPlayers)
{
	TableDeck = CardDeck(amountOfPacksInDeck);
	TableDealer = Dealer();
	MoveSelect = MoveSelector();

	for (int i = 0; i < amountOfPlayers; i++)
		Players.push_back(Player());
}

BlackJackTable::~BlackJackTable()
{
}

void BlackJackTable::playRound()
{
	deal();
	playersMoves();
	dealersMoves();
	storeResults();

	clearTable();
};

void BlackJackTable::deal()
{
	dealEachPlayerACard();
	TableDealer.addDownCard(TableDeck.drawDealerHiddenCard());

	dealEachPlayerACard();
	TableDealer.addUpCard(TableDeck.drawCard());

	showPlayersDealersUpCard();
};

void BlackJackTable::dealEachPlayerACard()
{
	for (Player &player : Players)
		player.addCardToHand(TableDeck.drawCard());	
};

void BlackJackTable::showPlayersDealersUpCard()
{
	for (Player &player : Players)
		player.setDealersUpCard(TableDealer.getUpCard());
};

void BlackJackTable::playersMoves()
{
	for (Player &player : Players)
	{
		HandState currentState = player.getHandState(TableDeck.getCurrentRealCount());

		while (playerHits(player, currentState))
		{
			player.hit(TableDeck.drawCard());
			currentState = player.getHandState(TableDeck.getCurrentRealCount());
		}

		player.stand();
	}
};

bool BlackJackTable::playerHits(Player &player, HandState &currentState)
{
	if (player.handAtMaxSize())
		return false;
	
	if (MoveSelect.move(currentState, TableDeck.getCurrentRealCount()) == 'H')
		return true;

	return false;
};

void BlackJackTable::dealersMoves()
{
	// Dealer flips the down card which adds it to the card count before dealing his cards.
	TableDeck.updateIndex(TableDealer.getDownCard());

	while (TableDealer.dealerHits())
	{
		TableDealer.addCardToHand(TableDeck.drawCard());
	}
};

void BlackJackTable::storeResults()
{
	if (IsMoveFindingMode)
	{
		MoveSamplerHandler handler = MoveSamplerHandler(TableDealer, Players);
		handler.getResults();
	}

	else
	{
		OddsSamplerHandler handler = OddsSamplerHandler(TableDealer, Players);
		handler.getResults();
	}
};

void BlackJackTable::clearTable()
{
	TableDealer.resetHand();

	for (Player &player : Players)
		player.resetHand();

	TableDeck.reshuffleDeck();
};