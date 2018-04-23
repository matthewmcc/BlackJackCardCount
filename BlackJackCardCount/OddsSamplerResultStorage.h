#include "stdafx.h"

#include <map>
#include <mutex>

// Stores all results for an index.
struct IndexResults
{
	std::map<double, int> HandResults =
		{ { BlackJack::LOSS, 0 },{ BlackJack::PUSH, 0 },
		{ BlackJack::WIN, 0 },{ BlackJack::BLACK_JACK_WIN, 0 } };

	void addResult(double betMultipler)
	{
		HandResults[betMultipler]++;
	}
};

#pragma once
// Stores all black jack hand results oreder by index and prints stored results to...
// ...the console.
class OddsSamplerResultStorage
{
public:
	static OddsSamplerResultStorage* getInstance()
	{
		if (instance == 0)
			instance = new OddsSamplerResultStorage();

		return instance;

	};

	void handPlayed() {
		HandsPlayedMutex.lock();
		HandsPlayed++;
		HandsPlayedMutex.unlock();
	};
	int getHandsPlayed() { return HandsPlayed; };

	void storeResult(int, double);

	void printResults();

private:
	static OddsSamplerResultStorage* instance;

	OddsSamplerResultStorage();
	~OddsSamplerResultStorage();

	std::map<double, double> OUTCOME_VALUE =
	{ { BlackJack::LOSS, -1 },{ BlackJack::PUSH, 0 },
	{ BlackJack::WIN, 1 },{ BlackJack::BLACK_JACK_WIN, 1.5 } };

	std::map<int, IndexResults> HandResultsByIndex;

	std::mutex WriteMutex;

	double WinLossTally;
	double TotalPlayed;

	double HandsPlayed;
	std::mutex HandsPlayedMutex;

	void addNewIndexResults(int);
};

