#include "CardDeck.h"

#include <map>
#include <list>
#include <mutex>

// Complete hand state used as an index to store and sort MoveFunctions and HandResults.
struct HandState
{
	bool PlayersScoreIsSoft;
	int PlayersScore;

	int DealersUpCardValue;

	int Index;

	// Operator for <map> storage
	bool operator<(const HandState& a) const
	{
		if (PlayersScoreIsSoft != a.PlayersScoreIsSoft)
			return PlayersScoreIsSoft < a.PlayersScoreIsSoft;

		if (PlayersScore != a.PlayersScore)
			return PlayersScore < a.PlayersScore;

		if (DealersUpCardValue != a.DealersUpCardValue)
			return DealersUpCardValue < a.DealersUpCardValue;

		return Index < a.Index;
	}

	bool stateEqualButIndex(HandState& stateToTest)
	{
		return (DealersUpCardValue == stateToTest.DealersUpCardValue &&
			PlayersScore == stateToTest.PlayersScore &&
			PlayersScoreIsSoft == stateToTest.PlayersScoreIsSoft);
	}
};

// The complete calculated state of a hand.
struct HandResult
{
	HandResult(HandState& handState) { HandState = handState; }

	HandState HandState;

	char PlayersMove;
	double Result;

	inline bool isSoft() { return HandState.PlayersScoreIsSoft; };
	inline int playersScore() { return HandState.PlayersScore; };

	inline int dealersUpCardValue() { return HandState.DealersUpCardValue; };

	inline double index() { return HandState.Index; };
};

// Lists to store each result type by players move. Hit or Stand.
struct HandStateResults
{
	HandStateResults()
	{
		StandResults = { { BlackJack::LOSS, 0 },{ BlackJack::PUSH, 0 },
			{ BlackJack::WIN, 0 },{ BlackJack::BLACK_JACK_WIN, 0 } };

		HitResults = { { BlackJack::LOSS, 0 },{ BlackJack::PUSH, 0 },
			{ BlackJack::WIN, 0 },{ BlackJack::BLACK_JACK_WIN, 0 } };
	};

	std::map<double, int> StandResults;
	std::map<double, int> HitResults;
};

#pragma once
// Stores HandResults by HandStates to be used to calculate Black Jack MoveFunctions.
class MoveSamplerResultStorage
{
public:
	static MoveSamplerResultStorage* getInstance()
	{
		if (instance == 0)
			instance = new MoveSamplerResultStorage();

		return instance;

	};

	void storeResult(HandResult&);

	void updateScoreToStore(bool isHard, int playerScoreToStore)
	{
		PlayerScoreToStoreIsHard = isHard;
		PlayerScoreToStore = playerScoreToStore;
	};

	void clearResults();

	std::map<HandState, HandStateResults> getResults() { return ResultsCounter; }

	void handPlayed() { 
		HandsPlayedMutex.lock();
		HandsPlayed++;
		HandsPlayedMutex.unlock();
	};
	int getHandsPlayed() { return HandsPlayed; };

private:
	static MoveSamplerResultStorage* instance;

	std::list<HandResult> BufferedResults;
	std::map<HandState, HandStateResults> ResultsCounter;

	std::mutex WriteMutex;
	std::mutex HandsPlayedMutex;

	bool PlayerScoreToStoreIsHard = true;
	int PlayerScoreToStore = 20;

	int HandsPlayed;

	int MIN_LIST_FILE_SIZE = 1000;

	MoveSamplerResultStorage();
	~MoveSamplerResultStorage();

	bool resultToBeStored(HandResult&);

	void incrementResult(HandResult&);
	void addResultSet(HandState&);
};