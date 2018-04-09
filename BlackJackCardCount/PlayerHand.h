#include "Player.h"
#include "CardDeck.h"

#include <list>

#pragma once
class PlayerHand
{
public:
	PlayerHand();
	~PlayerHand();

private:
	Player HandOwner;

	std::list<Card> CardsInHand;
};

