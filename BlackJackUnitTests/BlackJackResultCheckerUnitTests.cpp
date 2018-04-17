#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\BlackJackCardCount\BlackJack.h"
#include "..\BlackJackCardCount\BlackJack.cpp"

#include "../BlackJackCardCount/BlackJackResultChecker.h"
#include "../BlackJackCardCount/BlackJackResultChecker.cpp"

//#include "../BlackJackCardCount/HandScoreCalculator.h"
//#include "../BlackJackCardCount/HandScoreCalculator.cpp"

#include "../BlackJackCardCount/Dealer.h"
//#include "../BlackJackCardCount/Dealer.cpp"

#include "../BlackJackCardCount/Player.h"
//#include "../BlackJackCardCount/Player.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackJackUnitTests
{
	TEST_CLASS(BlackJackResultCheckerUnitTests)
	{
	public:
		TEST_METHOD(DealerBust)
		{
			Dealer bustDealer = createBustDealer();

			Player bustPlayer = createBustPlayer();
			Player aceBustPlayer = createAceBustPlayer();
			Player blackJackPlayer = createBlackJackPlayer();
			Player twentyPlayer = create20Player();
			Player eightteenPlayer = create18Player();

			BlackJackResultChecker resultChecker = BlackJackResultChecker(bustDealer);

			// With a bust player
			resultChecker.addNextPlayer(bustPlayer);
			Assert::AreEqual(0.0, resultChecker.getBetMultiplier());

			// With an ace bust player
			resultChecker.addNextPlayer(aceBustPlayer);
			Assert::AreEqual(0.0, resultChecker.getBetMultiplier());

			// With a player with a black jack
			resultChecker.addNextPlayer(blackJackPlayer);
			Assert::AreEqual(2.5, resultChecker.getBetMultiplier());

			// With a player with a score of 20
			resultChecker.addNextPlayer(twentyPlayer);
			Assert::AreEqual(2.0, resultChecker.getBetMultiplier());

			// With a player with a score of 18
			resultChecker.addNextPlayer(eightteenPlayer);
			Assert::AreEqual(2.0, resultChecker.getBetMultiplier());
		}

		TEST_METHOD(DealerAceBust)
		{
			Dealer aceBustDealer = createAceBustDealer();

			Player bustPlayer = createBustPlayer();
			Player aceBustPlayer = createAceBustPlayer();
			Player blackJackPlayer = createBlackJackPlayer();
			Player twentyPlayer = create20Player();
			Player eightteenPlayer = create18Player();

			BlackJackResultChecker resultChecker = BlackJackResultChecker(aceBustDealer);

			// With a bust player
			resultChecker.addNextPlayer(bustPlayer);
			Assert::AreEqual(0.0, resultChecker.getBetMultiplier());

			// With an ace bust player
			resultChecker.addNextPlayer(aceBustPlayer);
			Assert::AreEqual(0.0, resultChecker.getBetMultiplier());

			// With a player with a black jack
			resultChecker.addNextPlayer(blackJackPlayer);
			Assert::AreEqual(2.5, resultChecker.getBetMultiplier());

			// With a player with a score of 20
			resultChecker.addNextPlayer(twentyPlayer);
			Assert::AreEqual(2.0, resultChecker.getBetMultiplier());

			// With a player with a score of 18
			resultChecker.addNextPlayer(eightteenPlayer);
			Assert::AreEqual(2.0, resultChecker.getBetMultiplier());
		}

		TEST_METHOD(DealerBlackJack)
		{
			Dealer blackJackDealer = createBlackJackDealer();

			Player bustPlayer = createBustPlayer();
			Player aceBustPlayer = createAceBustPlayer();
			Player blackJackPlayer = createBlackJackPlayer();
			Player twentyPlayer = create20Player();
			Player eightteenPlayer = create18Player();

			BlackJackResultChecker resultChecker = BlackJackResultChecker(blackJackDealer);

			// With a bust player
			resultChecker.addNextPlayer(bustPlayer);
			Assert::AreEqual(0.0, resultChecker.getBetMultiplier());

			// With an ace bust player
			resultChecker.addNextPlayer(aceBustPlayer);
			Assert::AreEqual(0.0, resultChecker.getBetMultiplier());

			// With a player with a black jack
			resultChecker.addNextPlayer(blackJackPlayer);
			Assert::AreEqual(1.0, resultChecker.getBetMultiplier());

			// With a player with a score of 20
			resultChecker.addNextPlayer(twentyPlayer);
			Assert::AreEqual(0.0, resultChecker.getBetMultiplier());

			// With a player with a score of 18
			resultChecker.addNextPlayer(eightteenPlayer);
			Assert::AreEqual(0.0, resultChecker.getBetMultiplier());
		}

		TEST_METHOD(DealerNineteen)
		{
			Dealer nineteenDealer = create19Dealer();

			Player bustPlayer = createBustPlayer();
			Player aceBustPlayer = createAceBustPlayer();
			Player blackJackPlayer = createBlackJackPlayer();
			Player twentyPlayer = create20Player();
			Player eightteenPlayer = create18Player();

			BlackJackResultChecker resultChecker = BlackJackResultChecker(nineteenDealer);

			// With a bust player
			resultChecker.addNextPlayer(bustPlayer);
			Assert::AreEqual(0.0, resultChecker.getBetMultiplier());

			// With an ace bust player
			resultChecker.addNextPlayer(aceBustPlayer);
			Assert::AreEqual(0.0, resultChecker.getBetMultiplier());

			// With a player with a black jack
			resultChecker.addNextPlayer(blackJackPlayer);
			Assert::AreEqual(2.5, resultChecker.getBetMultiplier());

			// With a player with a score of 20
			resultChecker.addNextPlayer(twentyPlayer);
			Assert::AreEqual(2.0, resultChecker.getBetMultiplier());

			// With a player with a score of 18
			resultChecker.addNextPlayer(eightteenPlayer);
			Assert::AreEqual(2.0, resultChecker.getBetMultiplier());
		}

	private:
		Dealer createBlackJackDealer() {
			Dealer tableDealer = Dealer();

			tableDealer.addCardToHand(Card('H', 10));
			tableDealer.addCardToHand(Card('D', 1));

			return tableDealer;
		}

		Dealer create19Dealer() {
			Dealer tableDealer = Dealer();

			tableDealer.addCardToHand(Card('H', 10));
			tableDealer.addCardToHand(Card('D', 6));

			return tableDealer;
		}

		Dealer createBustDealer() {
			Dealer tableDealer = Dealer();

			tableDealer.addCardToHand(Card('H', 10));
			tableDealer.addCardToHand(Card('D', 4));
			tableDealer.addCardToHand(Card('S', 8));

			return tableDealer;
		}

		Dealer createAceBustDealer() {
			Dealer tableDealer = Dealer();

			tableDealer.addCardToHand(Card('H', 1));
			tableDealer.addCardToHand(Card('D', 4));
			tableDealer.addCardToHand(Card('C', 10));
			tableDealer.addCardToHand(Card('D', 13));

			return tableDealer;
		}

		Player createBustPlayer() {
			Player player = Player();

			player.addCardToHand(Card('D', 10));
			player.addCardToHand(Card('S', 4));
			player.addCardToHand(Card('C', 9));

			return player;
		}

		Player createAceBustPlayer() {
			Player player = Player();

			player.addCardToHand(Card('D', 4));
			player.addCardToHand(Card('S', 1));
			player.addCardToHand(Card('C', 1));
			player.addCardToHand(Card('H', 10));
			player.addCardToHand(Card('C', 7));

			return player;
		}

		Player createBlackJackPlayer() {
			Player player = Player();

			player.addCardToHand(Card('H', 10));
			player.addCardToHand(Card('D', 1));

			return player;
		}

		Player create20Player() {
			Player player = Player();

			player.addCardToHand(Card('D', 10));
			player.addCardToHand(Card('S', 10));

			return player;
		}

		Player create18Player() {
			Player player = Player();

			player.addCardToHand(Card('D', 10));
			player.addCardToHand(Card('S', 8));

			return player;
		}
	};
}