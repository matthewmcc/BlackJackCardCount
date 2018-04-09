#include "stdafx.h"
#include "MoveFinderResultStorage.h"
#include "BlackJackResultToCSV.h"

MoveFinderResultStorage* MoveFinderResultStorage::instance = 0;

MoveFinderResultStorage::MoveFinderResultStorage()
{
	BufferedResults = std::list<HandResult>();
	ResultsCounter = std::map<HandState, HandStateResults>();

	HandsPlayed = 0;
}

MoveFinderResultStorage::~MoveFinderResultStorage()
{
}
 
void MoveFinderResultStorage::storeResult(HandResult& handResult)
{
	if (resultToBeStored(handResult))
		incrementResult(handResult);
};

bool MoveFinderResultStorage::resultToBeStored(HandResult& handResult)
{
	if (!handResult.isSoft() == PlayerScoreToStoreIsHard
		&& handResult.playersScore() == PlayerScoreToStore)
		return true;

	return false;
};

void MoveFinderResultStorage::incrementResult(HandResult& handData)
{
	WriteMutex.lock();

	// Initialises result set if can't be found.
	if (ResultsCounter.find(handData.HandState) == ResultsCounter.end())
		addResultSet(handData.HandState); 

	if (handData.PlayersMove == 'S')
		ResultsCounter[handData.HandState].StandResults[handData.Result]++;
	else
		ResultsCounter[handData.HandState].HitResults[handData.Result]++;

	WriteMutex.unlock();
};
 
void MoveFinderResultStorage::addResultSet(HandState& handState)
{
	HandStateResults stateResults = HandStateResults();
	std::pair<HandState, HandStateResults> newResult = 
		std::pair<HandState, HandStateResults>(handState, stateResults);
	ResultsCounter.insert(newResult);
};

void MoveFinderResultStorage::bufferResult(HandResult& handResult)
{
	BufferedResults.push_back(handResult);
	fileResults();
};

void MoveFinderResultStorage::fileResults()
{
	if ((int) BufferedResults.size() >= MIN_LIST_FILE_SIZE)
	{
		flushBuffer();
	}
};

void MoveFinderResultStorage::flushBuffer()
{
	BlackJackResultToCSV* resultsToCSV = BlackJackResultToCSV::getInstance();
	resultsToCSV->writeToCSV(BufferedResults);
	BufferedResults = std::list<HandResult>();
};

void MoveFinderResultStorage::clearResults()
{
	BufferedResults.clear();
	ResultsCounter.clear();

	HandsPlayed = 0;
};