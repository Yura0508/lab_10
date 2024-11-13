#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_10_2_B/Lab_10_2_B.cpp" // Make sure this includes the Sort function

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:
        TEST_METHOD(TestSort)
        { 
            const int N = 3;
            Student students[N] = {
                {"Иванов", 2, COMPUTER_SCIENCE, {5, 4, 3}}, 
                {"Петров", 1, INFORMATIKA, {4, 5, 4}},      
                {"Сидоров", 3, PHYSICS_AND_INFORMATICS, {3, 4, 5}} 
            };

            
            Student expected[N] = {
                {"Петров", 1, INFORMATIKA, {4, 5, 4}},
                {"Иванов", 2, COMPUTER_SCIENCE, {5, 4, 3}},
                {"Сидоров", 3, PHYSICS_AND_INFORMATICS, {3, 4, 5}}
                         
            };

          
            Sort(students, N);

            
            for (int i = 0; i < N; i++) {
                Assert::AreEqual(expected[i].prizv, students[i].prizv);
                Assert::AreEqual(expected[i].kurs, students[i].kurs);
                Assert::AreEqual(static_cast<int>(expected[i].spec), static_cast<int>(students[i].spec));
                Assert::AreEqual(expected[i].subject.fizika, students[i].subject.fizika);
                Assert::AreEqual(expected[i].subject.matematika, students[i].subject.matematika);

                switch (students[i].spec) {
                case COMPUTER_SCIENCE:
                    Assert::AreEqual(expected[i].subject.programming, students[i].subject.programming);
                    break;
                case INFORMATIKA:
                    Assert::AreEqual(expected[i].subject.numerical_methods, students[i].subject.numerical_methods);
                    break;
                default:
                    Assert::AreEqual(expected[i].subject.pedagogy, students[i].subject.pedagogy);
                    break;
                }
            }
        }
    };
}