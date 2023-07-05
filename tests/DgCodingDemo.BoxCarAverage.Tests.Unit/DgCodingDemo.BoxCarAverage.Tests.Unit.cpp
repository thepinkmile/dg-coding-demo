#include "pch.h"
#include "CppUnitTest.h"
#include "TestHelpers.hpp"
#include "BoxCarAverage.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DgCodingDemoBoxCarAverageTestsUnit
{
	TEST_CLASS(DgCodingDemoBoxCarAverageTestsUnit)
	{
	public:

		TEST_METHOD(Should_Calculate_BoxCarAverage_For_Problem_Example)
		{
			std::array<int, 10> input = { { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } };
			std::array<int, 10> expected = { { 1, 1, 2, 3, 4, 5, 6, 7, 8, 9 } };

			auto actual = BoxCarAverage<int, 10, 3>::Calculate(input);

			Assert::AreEqual<std::array<int, 10>>(expected, actual);
		}

		TEST_METHOD(Should_Calculate_BoxCarAverage_For_Int)
		{
			std::array<int, 10> input = { { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } };
			std::array<int, 10> expected = { { 1, 1, 2, 2, 3, 4, 5, 6, 7, 8 } };

			auto actual = BoxCarAverage<int, 10, 5>::Calculate(input);

			Assert::AreEqual<std::array<int, 10>>(expected, actual);
		}

		TEST_METHOD(Should_Calculate_BoxCarAverage_For_Double)
		{
			std::array<double, 10> input = { { 1.0, 2.5, 3.0, 4.5, 5.0, 6.5, 7.0, 8.5, 9.5, 10.0 } };
			std::array<double, 10> expected = { { 1.0, 1.75, 2.1666666666666665, 2.75, 3.2000000000000002, 4.2999999999999998, 5.2000000000000002, 6.2999999999999998, 7.2999999999999998, 8.3000000000000007 } };

			auto actual = BoxCarAverage<double, 10, 5>::Calculate(input);

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(Should_Calculate_BoxCarAverage_For_Float)
		{
			std::array<float, 10> input = { { 1.0F, 2.5F, 3.0F, 4.5F, 5.0F, 6.5F, 7.0F, 8.5F, 9.5F, 10.0F } };
			std::array<float, 10> expected = { { 1.0F, 1.75F, 2.1666666666666665F, 2.75F, 3.2000000000000002F, 4.2999999999999998F, 5.2000000000000002F, 6.2999999999999998F, 7.2999999999999998F, 8.3000000000000007F } };

			auto actual = BoxCarAverage<float, 10, 5>::Calculate(input);

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(Should_Calculate_BoxCarAverage_Using_Bigger_Frame_Size_Than_Array)
		{
			std::array<int, 10> input = { { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } };
			std::array<int, 10> expected = { { 1, 1, 2, 2, 3, 3, 4, 4, 5, 5 } };

			auto actual = BoxCarAverage<int, 10, 12>::Calculate(input);

			Assert::AreEqual<std::array<int, 10>>(expected, actual);
		}
	};
}
