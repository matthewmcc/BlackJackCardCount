#include <map>

#pragma once
class OddsFinderResultStorage
{
public:
	static OddsFinderResultStorage* getInstance()
	{
		if (instance == 0)
			instance = new OddsFinderResultStorage();

		return instance;

	};

	void storeResult(double);

	void printResults();

private:
	static OddsFinderResultStorage* instance;

	OddsFinderResultStorage();
	~OddsFinderResultStorage();

	std::map<double, int> BetMultiplerResults = { {0.0, 0}, {1.0, 0}, {2.0, 0}, {2.5, 0} };

	double WinLossTally;
	double TotalPlayed;
};

