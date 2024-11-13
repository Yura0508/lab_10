#include "pch.h"
#include "CppUnitTest.h"
#include "../lab_10_2_A/lab_10_2_A.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestBinSearch)
        {
            Student students[3] = {
                {"Ivanov", 2, INFORMATIKA, {5, 4, 3}},
                {"Petrov", 1, COMPUTER_SCIENCE, {4, 5, 5}},
                {"Sidorov", 3, MATHEMATICS_AND_ECONOMICS, {3, 5, 4}}
            };

            // Perform binary search for student Petrov with specific criteria
            int foundIndex = BinSearch(students, 3, "Petrov", COMPUTER_SCIENCE, 5);
            Assert::AreEqual(foundIndex, 1); // Petrov is at index 1

            // Test not found
            foundIndex = BinSearch(students, 3, "Kozak", INFORMATIKA, 5);
            Assert::AreEqual(foundIndex, -1); // Kozak should not be found
        }



    };
}