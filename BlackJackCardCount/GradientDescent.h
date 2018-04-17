#include "LeastSquaresRegression.h"

#pragma once
class GradientDescent
{
public:
	GradientDescent(RegressionLists);
	~GradientDescent();

	RegressionLists DataLists;

	LinearFunction calculateLine();

	double NumberOfPoints = 0.0;

private:
	double AWeight;
	double BWeight;

	double YMin, YMax, YDiff, XMin, XMax, XDiff;

	double LearningRate = 0.01;
	int TrainingIterations = 10;

	void trainWeights();

	double randomDecimal();
	
	double predictedY(double);
	double yPredictedYDifference(double, double);

	void updateWeights(double, double);

	double sigmoidA(double);
	double sigmoidB(double, double);
	double sumOfSquaredErrors(double);
};

