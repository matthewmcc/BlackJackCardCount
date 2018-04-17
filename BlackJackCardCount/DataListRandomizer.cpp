#include "stdafx.h"
#include "DataListRandomizer.h"

#include <vector>
#include <algorithm>

DataListRandomizer::DataListRandomizer()
{
}


DataListRandomizer::~DataListRandomizer()
{
}

RegressionLists DataListRandomizer::randomizeDataLists(RegressionLists &dataLists)
{
	//NewDataLists = RegressionLists();

	//mulitplyDataByCounts(dataLists);
	//
	//mergeRandomizer(
	//	std::pair<std::list<double>&, std::list<double>&>(dataLists.X, dataLists.Y));

	//return NewDataLists;

	listsToVectors(dataLists);

	quickUnsort(0, X.size());

	RegressionLists newDataLists;
	for (int i = 0; i < X.size(); i++)
	{
		newDataLists.addDataInstance(X[i], Y[i], 1);
	}

	return newDataLists;
};

//void DataListRandomizer::mulitplyDataByCounts(RegressionLists &dataLists)
//{
//	std::list<double>::iterator xIterator = dataLists.X.begin();
//	std::list<double>::iterator yIterator = dataLists.Y.begin();
//	std::list<double>::iterator countsIterator = dataLists.Counts.begin();
//
//	while (xIterator != dataLists.X.end())
//	{
//		double x = *xIterator, y = *yIterator, count = *countsIterator;
//
//		for (int i = 0; i < count - 1; i++)
//		{
//			dataLists.addDataInstance(x, y, 1);
//		}
//
//		*countsIterator = 1;
//
//		xIterator++; yIterator++; countsIterator++;
//	}
//};
//
//void DataListRandomizer::mergeRandomizer
//	(std::pair<std::list<double>&, std::list<double>&> listsToSplit)
//{
//	if (listsToSplit.first.size() <= 1)
//	{
//		NewDataLists.addDataInstance(listsToSplit.first.front(), listsToSplit.second.front(), 1);
//
//		return;
//	}
//
//	if (listsToSplit.first.size() <= 2)
//	{
//		if (rand() % 2 == 0)
//		{
//			NewDataLists.addDataInstance(listsToSplit.first.front(), listsToSplit.second.front(), 1);
//			NewDataLists.addDataInstance(listsToSplit.first.back(), listsToSplit.second.back(), 1);
//
//			return;
//		}
//		else
//		{
//			NewDataLists.addDataInstance(listsToSplit.first.back(), listsToSplit.second.back(), 1);
//			NewDataLists.addDataInstance(listsToSplit.first.front(), listsToSplit.second.front(), 1);
//
//			return;
//		}
//	}
//
//	std::list<double>::iterator firstMiddle = std::next(listsToSplit.first.begin(), listsToSplit.first.size() / 2);
//	std::list<double>::iterator secondMiddle = std::next(listsToSplit.second.begin(), listsToSplit.second.size() / 2);
//
//	std::list<double> leftFirstList(listsToSplit.first.begin(), firstMiddle);
//	std::list<double> leftSecondList(listsToSplit.second.begin(), secondMiddle);
//
//	std::list<double> rightFirstList(firstMiddle, listsToSplit.first.end());
//	std::list<double> rightSecondList(secondMiddle, listsToSplit.second.end());
//
//	if (rand() % 2 == 0)
//	{
//		mergeRandomizer(std::pair<std::list<double>&, std::list<double>&>(leftFirstList, leftSecondList));
//		mergeRandomizer(std::pair<std::list<double>&, std::list<double>&>(rightFirstList, rightSecondList));
//	}
//	else
//	{
//		mergeRandomizer(std::pair<std::list<double>&, std::list<double>&>(rightFirstList, rightSecondList));
//		mergeRandomizer(std::pair<std::list<double>&, std::list<double>&>(leftFirstList, leftSecondList));
//	}
//}

void DataListRandomizer::listsToVectors(RegressionLists &dataLists)
{
	std::list<double>::iterator xIterator = dataLists.X.begin();
	std::list<double>::iterator yIterator = dataLists.Y.begin();
	std::list<double>::iterator countsIterator = dataLists.Counts.begin();

	while (xIterator != dataLists.X.end())
	{
		double x = *xIterator, y = *yIterator, count = *countsIterator;

		for (int i = 0; i < count; i++)
		{
			X.push_back(x);
			Y.push_back(y);
		}

		xIterator++; yIterator++; countsIterator++;
	}
};

void DataListRandomizer::quickUnsort(int startIndex, int size)
{
	if (size <= 1)
		return;

	if (size == 2)
	{
		if (randomBool())
			swapListsValues(startIndex, startIndex + 1);
		
		return;
	}

	for (int left = startIndex, right = startIndex + size - 1; left < right; left++, right--)
	{
		if (randomBool())
			swapListsValues(left, right);
	}

	quickUnsort(startIndex, (size / 2) - 1);
	quickUnsort(startIndex + ceil(size / 2), ceil(size / 2));
};
	
inline bool DataListRandomizer::randomBool()
{
	return rand() % 2 == 0;
};

inline void DataListRandomizer::swapListsValues(int index1, int index2)
{
	std::swap(X[index1], X[index2]);
	std::swap(Y[index1], Y[index2]);
}