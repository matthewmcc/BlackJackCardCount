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

	DataLists = dataLists;
	NumberOfPoints = DataLists.X.size();
}


GradientDescent::~GradientDescent()
{
}

LinearFunction GradientDescent::calculateLine()
{
	trainWeights();

	return LinearFunction((BWeight * YDiff) + YMin, (AWeight * XDiff) + XMin);
};

void GradientDescent::trainWeights()
{
	double annealRate = LearningRate / TrainingIterations;

	for (int i = 0; i < TrainingIterations; i++)
	{
		randomizeData();

		std::list<double>::iterator xIterator = DataLists.X.begin();
		std::list<double>::iterator yIterator = DataLists.Y.begin();

		while (xIterator != DataLists.X.end())
		{
			double x = ((*xIterator) - XMin) / XDiff,
				y = ((*yIterator) - YMin) / YDiff;

			updateWeights(y, x);

			xIterator++; yIterator++;
		}

		LearningRate -= annealRate;
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

void GradientDescent::randomizeData()
{
	DataListRandomizer randomizer = DataListRandomizer();
	DataLists = randomizer.randomizeDataLists(DataLists);
};