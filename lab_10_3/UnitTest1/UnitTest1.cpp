#include "pch.h"
#include "CppUnitTest.h"
#include "../lab_10_3/lab_10_3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
        TEST_METHOD(TestAddProduct)
        {
            int count = 3;  // Initial product count
            Product products[3];  // Statically allocated array

            // Initialize products with different store names
            products[0].name = "Product1";
            products[0].storeName = "StoreB";
            products[0].price = 10.0;
            products[0].quantity = 5;
            products[0].unit = "pcs";

            products[1].name = "Product2";
            products[1].storeName = "StoreA";
            products[1].price = 20.0;
            products[1].quantity = 3;
            products[1].unit = "pcs";

            products[2].name = "Product3";
            products[2].storeName = "StoreC";
            products[2].price = 30.0;
            products[2].quantity = 8;
            products[2].unit = "pcs";

            
            sortByStore(products, count);

            
            Assert::AreEqual(products[0].storeName, std::string("StoreA"));
            Assert::AreEqual(products[1].storeName, std::string("StoreB"));
            Assert::AreEqual(products[2].storeName, std::string("StoreC"));

            Assert::AreEqual(products[0].name, std::string("Product2"));
            Assert::AreEqual(products[1].name, std::string("Product1"));
            Assert::AreEqual(products[2].name, std::string("Product3"));

        }
	};
}
