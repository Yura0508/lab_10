#include "pch.h"
#include "CppUnitTest.h"
#include "../lab_10_1_B/lab_10_1_B.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestCalcPhysicsHighGrades)
		{
			// Create an array of students with known physics grades
			Student students[] = {
				{ "Ivanov", 1, INFORMATIKA, {5, 4, 3} },
				{ "Petrov", 2, COMPUTER_SCIENCE, {4, 5, 4} },
				{ "Sidorov", 3, MATHEMATICS_AND_ECONOMICS, {3, 2, 5} },
				{ "Kovalenko", 1, PHYSICS_AND_INFORMATICS, {5, 5, 5} },
				{ "Shevchenko", 2, TECHNICAL_EDUCATION, {2, 3, 4} }
			};

			// Call the function under test
			double percentage = CalcPhysicsHighGrades(students, 5);

			// Expected percentage: 3 students (Ivanov, Petrov, Kovalenko) out of 5 have physics grades of 4 or 5
			// Expected result is (3 / 5) * 100 = 60.0
			Assert::AreEqual(60.0, percentage, 0.0001);
		}
	};
}
