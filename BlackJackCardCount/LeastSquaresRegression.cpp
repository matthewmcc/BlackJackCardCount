#include "stdafx.h"

#include "LeastSquaresRegression.h"

LeastSquaresRegression::~LeastSquaresRegression()
{
}

CartesianLinearFunction LeastSquaresRegression::calculateLine()
{
	calculateSums();

	double slope = calculateSlope();
	double yIntercept = calculateIntercept(slope);

	return CartesianLinearFunction(slope, yIntercept);
};

// Function is bloated for effiency. Multiple doubles must be calculated within one loop. 
void LeastSquaresRegression::calculateSums()
{
	std::list<double>::iterator xIterator = DataLists.X.begin();
	std::list<double>::iterator yIterator = DataLists.Y.begin();
	std::list<int>::iterator weightsIterator = DataLists.Weights.begin();

	while (xIterator != DataLists.X.end())
	{
		XSum += *xIterator * (double) *weightsIterator;
		YSum += *yIterator * (double) *weightsIterator;

		XYSum += (*xIterator * *yIterator) * (double)*weightsIterator;
		XSquaredSum += (*xIterator * *xIterator) * (double)*weightsIterator;

		NumberOfPoints += (double) *weightsIterator;

		xIterator++; yIterator++; weightsIterator++;
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