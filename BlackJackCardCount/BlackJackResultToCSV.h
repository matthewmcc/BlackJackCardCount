#include "MoveFinderResultStorage.h"

#include <fstream>
#include <list>

#pragma once
class BlackJackResultToCSV
{
public:
	static BlackJackResultToCSV* getInstance()
	{
		if (instance == 0)
			instance = new BlackJackResultToCSV();

		return instance;
	};

	void writeToCSV(std::list<HandResult>);

private:
	static BlackJackResultToCSV* instance;

	BlackJackResultToCSV();
	~BlackJackResultToCSV();

	std::string CSVFileName = "C:/Users/Matthew McCullough/Desktop/BlackJackResults/blackjack.csv";
};

