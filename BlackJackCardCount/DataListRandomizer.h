#include "LeastSquaresRegression.h"

#include <vector>

#pragma once
class DataListRandomizer
{
public:
	DataListRandomizer();
	~DataListRandomizer();

	RegressionLists randomizeDataLists(RegressionLists&);

private:
	RegressionLists NewDataLists;
	std::vector<double> X, Y;

	void mulitplyDataByCounts(RegressionLists&);

	void mergeRandomizer(std::pair<std::list<double>&, std::list<double>&>);

	void listsToVectors(RegressionLists&);

	void quickUnsort(int, int);

	inline bool randomBool();
	inline void swapListsValues(int, int);
};
