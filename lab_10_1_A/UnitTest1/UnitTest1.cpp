#include "pch.h"
#include "CppUnitTest.h"
#include "../lab_10_1_A/lab_10_1_A.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        Student* students;
        int N;

        TEST_METHOD_INITIALIZE(Init)
        {
            N = 5;  // Let's create 5 students
            students = new Student[N];

            // Test data: Physics grades (only grades 4 and 5 count as high grades)
            students[0] = { "Ivanov", 1, INFORMATIKA, {5, 4, 3} };
            students[1] = { "Petrov", 2, COMPUTER_SCIENCE, {4, 5, 4} };
            students[2] = { "Sidorov", 3, MATHEMATICS_AND_ECONOMICS, {3, 2, 5} };
            students[3] = { "Kovalenko", 1, PHYSICS_AND_INFORMATICS, {5, 5, 5} };
            students[4] = { "Shevchenko", 2, TECHNICAL_EDUCATION, {2, 3, 4} };
        }

        TEST_METHOD_CLEANUP(Cleanup)
        {
            delete[] students;
        }

        TEST_METHOD(TestCalcPhysicsHighGrades)
        {
            double percentage = CalcPhysicsHighGrades(students, N);
            // We expect 3 students out of 5 to have grades 4 or 5 in Physics (Ivanov, Petrov, Kovalenko)
            // The expected percentage is (3 / 5) * 100 = 60%
            Assert::AreEqual(percentage, 60.0, 0.0001);
        }
    };
}