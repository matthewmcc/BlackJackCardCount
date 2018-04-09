#include "CardDeck.h"

#include <map>
#include <list>
#include <mutex>

struct HandState
{
	bool PlayersScoreIsSoft;
	int PlayersScore;

	int DealersUpCardValue;

	double Index;

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

struct HandStateResults
{
	HandStateResults()
	{
		StandResults = { {0.0, 0}, {1.0, 0}, {2.0, 0}, {2.5, 0} };
		HitResults = { {0.0, 0}, {1.0, 0}, {2.0, 0}, {2.5, 0} };
	};

	std::map<double, int> StandResults;
	std::map<double, int> HitResults;
};

#pragma once
class MoveFinderResultStorage
{
public:
	static MoveFinderResultStorage* getInstance()
	{
		if (instance == 0)
			instance = new MoveFinderResultStorage();

		return instance;

	};

	void storeResult(HandResult&);

	void updateScoreToStore(bool isHard, int playerScoreToStore)
	{
		PlayerScoreToStoreIsHard = isHard;
		PlayerScoreToStore = playerScoreToStore;
	};

	void flushBuffer();
	void clearResults();

	std::map<HandState, HandStateResults> getResults() { return ResultsCounter; }

	void handPlayed() { 
		HandsPlayedMutex.lock();
		HandsPlayed++;
		HandsPlayedMutex.unlock();
	};
	int getHandsPlayed() { return HandsPlayed; };

private:
	static MoveFinderResultStorage* instance;

	std::list<HandResult> BufferedResults;
	std::map<HandState, HandStateResults> ResultsCounter;

	std::mutex WriteMutex;
	std::mutex HandsPlayedMutex;

	bool PlayerScoreToStoreIsHard = true;
	int PlayerScoreToStore = 20;

	int HandsPlayed;

	int MIN_LIST_FILE_SIZE = 1000;

	MoveFinderResultStorage();
	~MoveFinderResultStorage();

	bool resultToBeStored(HandResult&);

	void incrementResult(HandResult&);
	void addResultSet(HandState&);

	void bufferResult(HandResult&);
	void fileResults();
};