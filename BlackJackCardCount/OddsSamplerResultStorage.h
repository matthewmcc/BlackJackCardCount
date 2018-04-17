//#include "BlackJack.h"
#include "stdafx.h"

#include <map>

#pragma once
class OddsSamplerResultStorage
{
public:
	static OddsSamplerResultStorage* getInstance()
	{
		if (instance == 0)
			instance = new OddsSamplerResultStorage();

		return instance;

	};

	void storeResult(double);

	void printResults();

private:
	static OddsSamplerResultStorage* instance;

	OddsSamplerResultStorage();
	~OddsSamplerResultStorage();

	std::map<double, int> BetMultiplerResults = 
		{ {BlackJack::LOSS, 0}, {BlackJack::PUSH, 0}, 
		{BlackJack::WIN, 0}, {BlackJack::BLACK_JACK_WIN, 0} };

	double WinLossTally;
	double TotalPlayed;
};

