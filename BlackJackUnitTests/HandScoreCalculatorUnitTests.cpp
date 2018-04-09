#include "stdafx.h"
#include "CppUnitTest.h"

#include "../BlackJackCardCount/HandScoreCalculator.h"
#include "../BlackJackCardCount/HandScoreCalculator.cpp"

#include "../BlackJackCardCount/Dealer.h"
#include "../BlackJackCardCount/Dealer.cpp"

#include "../BlackJackCardCount/Player.h"
#include "../BlackJackCardCount/Player.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackJackUnitTests
{
	TEST_CLASS(HandScoreCalculatorUnitTests)
	{
	public:
		TEST_METHOD(ScoreCalculatorTests)
		{
			HandScoreCalculator scoreCalculator = HandScoreCalculator();

			std::list<Card> hand = create3CardBustHand();
			Assert::AreEqual(scoreCalculator.calculateScore(hand), 23);

			hand = create4CardBustHand();
			Assert::AreEqual(scoreCalculator.calculateScore(hand), 23);

			hand = create5CardBustHand();
			Assert::AreEqual(scoreCalculator.calculateScore(hand), 22);

			hand = createBlackJackHand();
			Assert::AreEqual(scoreCalculator.calculateScore(hand), 21);

			hand = create20Hand();
			Assert::AreEqual(scoreCalculator.calculateScore(hand), 20);

			hand = create18Hand();
			Assert::AreEqual(scoreCalculator.calculateScore(hand), 18);

			hand = create15Hand();
			Assert::AreEqual(scoreCalculator.calculateScore(hand), 15);
		}

		TEST_METHOD(SoftHardHandTests)
		{
			HandScoreCalculator scoreCalculator = HandScoreCalculator();

			std::list<Card> hand = create3CardBustHand();
			Assert::IsFalse(scoreCalculator.handIsSoft(hand));

			hand = create4CardBustHand();
			Assert::IsFalse(scoreCalculator.handIsSoft(hand));

			hand = create5CardBustHand();
			Assert::IsFalse(scoreCalculator.handIsSoft(hand));

			hand = create20Hand();
			Assert::IsFalse(scoreCalculator.handIsSoft(hand));

			hand = create18Hand();
			Assert::IsFalse(scoreCalculator.handIsSoft(hand));

			hand = create15Hand();
			Assert::IsFalse(scoreCalculator.handIsSoft(hand));

			hand = createBlackJackHand();
			Assert::IsTrue(scoreCalculator.handIsSoft(hand));

			hand = createSoft3CardHand();
			Assert::IsFalse(scoreCalculator.handIsSoft(hand));

			hand = createSoft4CardHand();
			Assert::IsTrue(scoreCalculator.handIsSoft(hand));

			hand = createSoft18Hand();
			Assert::IsTrue(scoreCalculator.handIsSoft(hand));
		}

	private:

		std::list<Card> create3CardBustHand() {
			std::list<Card> hand = { Card('D', 10), Card('S', 4), Card('C', 9) };

			return hand;
		}

		std::list<Card> create4CardBustHand() {
			std::list<Card> hand = { Card('D', 6), Card('S', 1), 
				Card('C', 12), Card('C', 6) };

			return hand;
		}

		std::list<Card> create5CardBustHand() {
			std::list<Card> hand = { Card('D', 5), Card('S', 1),
				Card('C', 13), Card('C', 1), Card('C', 5) };

			return hand;
		}

		std::list<Card> createBlackJackHand() {
			std::list<Card> hand = { Card('D', 10), Card('S', 1)};

			return hand;
		}

		std::list<Card> create20Hand() {
			std::list<Card> hand = { Card('D', 10), Card('S', 5), Card('C', 5) };

			return hand;
		}

		std::list<Card> create18Hand() {
			std::list<Card> hand = { Card('D', 6), Card('S', 6), Card('H', 6) };

			return hand;
		}

		std::list<Card> create15Hand() {
			std::list<Card> hand = { Card('D', 10), Card('S', 5)};

			return hand;
		}


		std::list<Card> createSoft3CardHand() {
			std::list<Card> hand = { Card('D', 4), Card('S', 1), Card('C', 9) };

			return hand;
		}

		std::list<Card> createSoft4CardHand() {
			std::list<Card> hand = { Card('D', 1), Card('S', 4),
				Card('C', 2), Card('C', 2) };

			return hand;
		}

		std::list<Card> createSoft18Hand() {
			std::list<Card> hand = { Card('D', 1), Card('S', 7)};

			return hand;
		}
	};
}