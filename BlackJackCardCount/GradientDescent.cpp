#include "stdafx.h"
#include "GradientDescent.h"
#include "DataListRandomizer.h"

#include <iostream>
#include <algorithm>

GradientDescent::GradientDescent(RegressionLists dataLists)
{
	AWeight = 0.5;
	BWeight = 0.5;

	XMin = *std::min_element(dataLists.X.begin(), dataLists.X.end());
	XMax = *std::max_element(dataLists.X.begin(), dataLists.X.end());
	XDiff = XMax - XMin;

	YMin = *std::min_element(dataLists.Y.begin(), dataLists.Y.end());
	YMax = *std::max_element(dataLists.Y.begin(), dataLists.Y.end());
	YDiff = YMax - YMin;

	std::cout << std::endl << "X, min, max, diff: " << XMin << ", " << XMax << ", " << XDiff << std::endl;
	std::cout << "Y, min, max, diff: " << YMin << ", " << YMax << ", " << YDiff << std::endl;

	DataListRandomizer randomizer = DataListRandomizer();
	dataLists = randomizer.randomizeDataLists(dataLists);

	DataLists = dataLists;
	NumberOfPoints = DataLists.X.size();
}


GradientDescent::~GradientDescent()
{
}

LinearFunction GradientDescent::calculateLine()
{
	trainWeights();

	std::cout << "Slope weight: " << BWeight << ", intercept: " << AWeight << std::endl;

	return LinearFunction((BWeight * YDiff) + YMin, (AWeight * XDiff) + XMin);
};

void GradientDescent::trainWeights()
{
	std::list<double>::iterator xIterator = DataLists.X.begin();
	std::list<double>::iterator yIterator = DataLists.Y.begin();

	for (int i = 0; i < TrainingIterations; i++)
	{
		while (xIterator != DataLists.X.end())
		{
			double x = ((*xIterator) - XMin) / XDiff,
				y = ((*yIterator) - YMin) / YDiff;

			updateWeights(y, x);

			xIterator++; yIterator++;
		}
	}
};

double GradientDescent::randomDecimal()
{
	return ((double) rand() / RAND_MAX);
};


void GradientDescent::updateWeights(double y , double x)
{
	double yDifference = yPredictedYDifference(y, x);

	AWeight -= LearningRate * sigmoidA(yDifference);
	BWeight -= LearningRate * sigmoidB(yDifference, x);
};

double GradientDescent::predictedY(double x)
{
	return AWeight + (BWeight * x);
};

double GradientDescent::yPredictedYDifference(double actualY, double x)
{
	return actualY - predictedY(x);
};

double GradientDescent::sigmoidA(double yDifference)
{
	return -yDifference;
};

double GradientDescent::sigmoidB(double yDifference, double x)
{
	return - (yDifference * x);
};

double GradientDescent::sumOfSquaredErrors(double yDifference)
{
	return 0.5 * pow(yDifference, 2);
};