#include "MoveFinderResultStorage.h"

#include <map>

#pragma once
class ResultsToConsole
{
public:
	static void PrintResults(std::map<HandState, HandStateResults>);
	static double CalculateWinOdds(std::map<double, int>);

private:

	ResultsToConsole();
	~ResultsToConsole();
};

