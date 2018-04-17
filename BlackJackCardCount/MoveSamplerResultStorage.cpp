#include "stdafx.h"
#include "MoveSamplerResultStorage.h"
#include "BlackJackResultToCSV.h"

MoveSamplerResultStorage* MoveSamplerResultStorage::instance = 0;

MoveSamplerResultStorage::MoveSamplerResultStorage()
{
	ResultsCounter = std::map<HandState, HandStateResults>();

	HandsPlayed = 0;
}

MoveSamplerResultStorage::~MoveSamplerResultStorage()
{
}
 
void MoveSamplerResultStorage::storeResult(HandResult& handResult)
{
	if (resultToBeStored(handResult))
		incrementResult(handResult);
};

bool MoveSamplerResultStorage::resultToBeStored(HandResult& handResult)
{
	if (!handResult.isSoft() == PlayerScoreToStoreIsHard
		&& handResult.playersScore() == PlayerScoreToStore)
		return true;

	return false;
};

void MoveSamplerResultStorage::incrementResult(HandResult& handData)
{
	WriteMutex.lock();

	// Initialises result set if can't be found.
	if (ResultsCounter.find(handData.HandState) == ResultsCounter.end())
		addResultSet(handData.HandState); 

	if (handData.PlayersMove == BlackJack::STAND)
		ResultsCounter[handData.HandState].StandResults[handData.Result]++;
	else
		ResultsCounter[handData.HandState].HitResults[handData.Result]++;

	WriteMutex.unlock();
};
 
void MoveSamplerResultStorage::addResultSet(HandState& handState)
{
	HandStateResults stateResults = HandStateResults();
	std::pair<HandState, HandStateResults> newResult = 
		std::pair<HandState, HandStateResults>(handState, stateResults);

	ResultsCounter.insert(newResult);
};


void MoveSamplerResultStorage::clearResults()
{
	ResultsCounter.clear();

	HandsPlayed = 0;
};