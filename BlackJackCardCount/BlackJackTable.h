#include "Dealer.h"
#include "Player.h"
#include "MoveSelector.h"

#include <list>

#pragma once
// Simulates rounds of Black Jack. Has 2 simulation modes. IsMoveFindingMode = True will...
// ...store randomly simulated moves results in a MoveSamplerResultStorage and IsMOveFindingMode = false...
// ...will use a populated MoveSelector to calculate which move to make and store the results in...
// ...OddsSamplerResultsStorage.
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
	void setIndexBeforeDeal();
	void dealEachPlayerACard();
	void showPlayersDealersUpCard();

	void playersMoves();
	inline bool playerHits(Player&, HandState&);

	void dealersMoves();

	void storeResults();

	void clearTable();
};
