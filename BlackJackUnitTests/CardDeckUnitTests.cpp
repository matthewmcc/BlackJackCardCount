#include "stdafx.h"
#include "CppUnitTest.h"

#include "../BlackJackCardCount/CardDeck.h"
#include "../BlackJackCardCount/CardDeck.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackJackUnitTests
{		
	TEST_CLASS(CardDeckUnitTests)
	{
	public:
		TEST_METHOD(CardEqualOpperator)
		{
			Card cardA = Card('H', 2);
			Card cardB = Card('H', 2);
			Card cardC = Card('D', 2);
			Card cardD = Card('H', 3);

			Assert::AreEqual(cardA == cardB, true);
			Assert::AreEqual(cardA == cardC, false);
			Assert::AreEqual(cardA == cardD, false);
		}
		
		TEST_METHOD(CardDeckInit)
		{
			CardDeck deck = CardDeck(1);

			Assert::AreEqual(deck.deckSize(), 52);

			deck = CardDeck(6);

			Assert::AreEqual(deck.deckSize(), 52 * 6);
		}

		TEST_METHOD(CardDeckDraw) {
			CardDeck deck = CardDeck(1);

			Card testCard = deck.drawCard();

			for (int i = 0; i < 51; i++)
				Assert::AreEqual(testCard == deck.drawCard(), false);
		}
	};
}