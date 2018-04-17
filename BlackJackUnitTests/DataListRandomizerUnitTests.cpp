#include "stdafx.h"
#include "CppUnitTest.h"

#include "../BlackJackCardCount/DataListRandomizer.h"
#include "../BlackJackCardCount/DataListRandomizer.cpp"

#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackJackUnitTests
{
	TEST_CLASS(DataListRandomizerUnitTests)
	{
	public:
		int listsSize = 100;

		TEST_METHOD(RandomizeDataLists)
		{
			RegressionLists lists = createRegressionLists();

			DataListRandomizer listsRandomizer = DataListRandomizer();

			lists = listsRandomizer.randomizeDataLists(lists);

			lists.X.sort();
			lists.Y.sort();

			std::list<double>::iterator xIterator = lists.X.begin();
			std::list<double>::iterator yIterator = lists.Y.begin();

			for (int i = 0; i < listsSize; i++)
			{
				Assert::AreEqual(*xIterator, (double) i);
				Assert::AreEqual(*yIterator, (double) i);

				xIterator++;
				yIterator++;
			}
		}
	
	private:
		RegressionLists createRegressionLists()
		{
			RegressionLists lists = RegressionLists();

			for (int i = 0; i < listsSize; i++)
			{
				lists.addDataInstance(i, i, 1);
			}

			return lists;
		}
	};
}