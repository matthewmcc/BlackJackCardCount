#include "Dealer.h"
#include "Player.h"
#include "MoveSelector.h"

#include <list>

#pragma once
class BlackJackTable
{
public:
	BlackJackTable() {};
	BlackJackTable(int amountOfPacksInDeck, int amountOfPlayers);
	~BlackJackTable();

	void playRound();

	// Changes how the results are stored by storing all moves made in a hand when selected to...
	// ...only storing final result moves.	
	void setToMoveFindingMode() { IsMoveFindingMode = true; };

private:
	CardDeck TableDeck;
	Dealer TableDealer;
	std::list<Player> Players;

	bool IsMoveFindingMode = false;
	MoveSelector MoveSelect;

	void deal();
	void dealEachPlayerACard();
	void showPlayersDealersUpCard();

	void playersMoves();
	inline bool playerHits(Player&, HandState&);

	void dealersMoves();

	void storeResults();

	void clearTable();
};
