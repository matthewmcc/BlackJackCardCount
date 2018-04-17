#include "stdafx.h"

#include "LeastSquaresRegression.h"

LeastSquaresRegression::~LeastSquaresRegression()
{
}

LinearFunction LeastSquaresRegression::calculateLine()
{
	calculateSums();

	double slope = calculateSlope();
	double yIntercept = calculateIntercept(slope);

	return LinearFunction(slope, yIntercept);
};

// Function is bloated for effiency. Multiple doubles must be calculated within one loop. 
void LeastSquaresRegression::calculateSums()
{
	std::list<double>::iterator xIterator = DataLists.X.begin();
	std::list<double>::iterator yIterator = DataLists.Y.begin();
	std::list<double>::iterator countsIterator = DataLists.Counts.begin();

	while (xIterator != DataLists.X.end())
	{
		double x = *xIterator, y = *yIterator, count = *countsIterator;

		XSum += x * count;
		YSum += y * count;

		XYSum += (x * y) * count;
		XSquaredSum += (x * x) * count;

		NumberOfPoints += count;

		xIterator++; yIterator++; countsIterator++;
	}
};

double LeastSquaresRegression::calculateSlope()
{
	return (NumberOfPoints * XYSum - XSum * YSum) /
		((NumberOfPoints * XSquaredSum) - (XSum * XSum));
};

double LeastSquaresRegression::calculateIntercept(double slope)
{
	return (YSum - slope * (XSum)) /
		NumberOfPoints;
};