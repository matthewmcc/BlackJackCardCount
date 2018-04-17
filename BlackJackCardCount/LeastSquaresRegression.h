#include <list>

struct RegressionLists
{
public:
	RegressionLists()
	{
		X = std::list<double>();
		Y = std::list<double>();
		Counts = std::list<double>();
	}

	RegressionLists(std::list<double> x, std::list<double> y, std::list<double> counts)
	{
		X = x;
		Y = y;
		Counts = counts;
	}

	void addDataInstance(double x, double y, double count)
	{
		X.push_back(x);
		Y.push_back(y);
		Counts.push_back(count);
	};

	std::list<double> X;
	std::list<double> Y;
	std::list<double> Counts;
};

struct LinearFunction
{
	LinearFunction() {};
	LinearFunction(double slope, double yIntercept)
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

	LinearFunction calculateLine();

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

