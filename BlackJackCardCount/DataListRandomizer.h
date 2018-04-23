#include "LeastSquaresRegression.h"

#include <vector>

#pragma once
// Multiples out regression list data by counts and randomises the data in the lists.
class DataListRandomizer
{
public:
	DataListRandomizer();
	~DataListRandomizer();

	RegressionLists randomizeDataLists(RegressionLists &dataLists);

private:
	RegressionLists NewDataLists;
	std::vector<double> X, Y;

	void listsToVectors(RegressionLists&);

	void quickUnsort(int, int);

	inline bool randomBool();
	inline void swapListsValues(int, int);
};
