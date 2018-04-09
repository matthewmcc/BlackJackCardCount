#include "stdafx.h"
#include "CppUnitTest.h"

#include "../BlackJackCardCount/LeastSquaresRegression.h"
#include "../BlackJackCardCount/LeastSquaresRegression.cpp"

#include <list>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackJackUnitTests
{
	TEST_CLASS(LeastSquaresRegressionUnitTests)
	{
	public:
		TEST_METHOD(CalculateLineTests)
		{
			std::list<double> x = getXList();
			std::list<double> y = getYList();
			std::list<int> weights = getWeightsList();

			RegressionLists lists = RegressionLists(x, y, weights);

			LeastSquaresRegression regression = LeastSquaresRegression(lists);

			CartesianLinearFunction linearFunction = regression.calculateLine();

			double slopeAnswer = 249.0 / 164.0;
			Assert::AreEqual(linearFunction.Slope, slopeAnswer);

			double yInterceptAnswer = (41.0 - slopeAnswer * 26.0) / 5.0;
			Assert::AreEqual(linearFunction.YIntercept, yInterceptAnswer);
		}

	private:
		std::list<double> getXList()
		{
			std::list<double> x = { 2, 3, 5, 7, 9 };
			return x;
		}

		std::list<double> getYList()
		{
			std::list<double> y = { 4, 5, 7, 10, 15 };
			return y;
		}

		std::list<int> getWeightsList()
		{
			std::list<int> weights = { 1, 1, 1, 1, 1 };
			return weights;
		}
	};
}