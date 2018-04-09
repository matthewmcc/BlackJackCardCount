#include <list>

struct RegressionLists
{
public:
	RegressionLists()
	{
		std::list<double> X = std::list<double>();
		std::list<double> Y = std::list<double>();
		std::list<int> Weights = std::list<int>();
	}

	RegressionLists(std::list<double> x, std::list<double> y, std::list<int> weights)
	{
		X = x;
		Y = y;
		Weights = weights;
	}

	void addDataInstance(double x, double y, int weight)
	{
		X.push_back(x);
		Y.push_back(y);
		Weights.push_back(weight);
	};

	std::list<double> X;
	std::list<double> Y;
	std::list<int> Weights;
};

struct CartesianLinearFunction
{
	CartesianLinearFunction() {};
	CartesianLinearFunction(double slope, double yIntercept)
	{
		Slope = slope;
		YIntercept = yIntercept;
	}

	double getYCoordinate(double xCoordinate)
	{
		return (Slope * xCoordinate) + YIntercept;
	}

	double Slope;
	double YIntercept;
};

#pragma once
class LeastSquaresRegression
{
public:
	LeastSquaresRegression(RegressionLists dataLists)
	{   
		DataLists = dataLists;

		XSum = 0.0, YSum = 0.0, XSquaredSum = 0.0, XYSum = 0.0, NumberOfPoints = 0;
	};
	~LeastSquaresRegression();

	CartesianLinearFunction calculateLine();

	double NumberOfPoints;

private:
	RegressionLists DataLists;

	double XSum;
	double YSum;
	double XSquaredSum;
	double XYSum;

	inline void calculateSums();
	inline double calculateSlope();
	inline double calculateIntercept(double);
};

