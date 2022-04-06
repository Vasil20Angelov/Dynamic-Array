#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "DynamicArray.h"

#include <vector>

TEST_CASE("Default constructed array has correct properties")
{
	DynamicArray<int> dArr;

	SECTION("getSize() returns 0")
	{
		REQUIRE(dArr.getSize() == 0);
	}
	SECTION("getCapacity() returns 0")
	{
		REQUIRE(dArr.getCapacity() == 0);
	}
}

void requireSameContents(DynamicArray<int>& da, std::vector<int> v)
{
	for (size_t i = 0; i < v.size(); ++i)
		REQUIRE(da[i] == v[i]);
}

TEST_CASE("Initialization list constructed object has correct properties")
{
	DynamicArray<int> dArr{ 4, 5, 6, 8 };
	std::vector<int> expected{ 4,5,6,8 };

	SECTION("getSize() returns 4")
	{
		REQUIRE(dArr.getSize() == 4);
	}
	SECTION("getCapacity() returns 4")
	{
		REQUIRE(dArr.getCapacity() == 4);
	}
	SECTION("Elements are stored correctly")
	{
		requireSameContents(dArr, expected);
	}
}

TEST_CASE("Copy-constructed dynamic array has correct properties")
{
	DynamicArray<int> original{ 4, 5, 6, 8 };
	DynamicArray<int> copy(original);
	std::vector<int> expected{ 4,5,6,8 };

	SECTION("getSize() returns 4")
	{
		REQUIRE(copy.getSize() == 4);
	}
	SECTION("getCapacity() returns 4")
	{
		REQUIRE(copy.getCapacity() == 4);
	}
	SECTION("Elements are stored correctly")
	{
		requireSameContents(copy, expected);
	}
}

TEST_CASE("Dynamic array constructed with specific size has correct properties") {
	DynamicArray<int> dArr(10);
	REQUIRE(dArr.getSize() == 0);
	REQUIRE(dArr.getCapacity() == 10);
}

TEST_CASE("at() correctly returns the contents of the array")
{
	DynamicArray<int> da{ 4, 5, 6, 8 };
	std::vector<int> expected{ 4,5,6,8 };
	for (size_t i = 0; i < expected.size(); ++i)
		REQUIRE(da.at(i) == expected.at(i));
}

TEST_CASE("at() throws when the index is out of range")
{
	DynamicArray<int> da{ 4, 5, 6, 8 };
	REQUIRE_THROWS_AS(da.at(4), std::out_of_range);
}

TEST_CASE("DynamicArray::at()")
{
	DynamicArray<int> da{ 4, 5, 6, 8 };

	SECTION("The elements of the array are returned correctly")
	{
		std::vector<int> expected{ 4,5,6,8 };
		for (size_t i = 0; i < expected.size(); ++i)
			REQUIRE(da.at(i) == expected.at(i));
	}
	SECTION("When the index is out of range, an exception is thrown")
	{
		REQUIRE_THROWS_AS(da.at(4), std::out_of_range);
	}
}


TEST_CASE("Test Resize") {
	
	DynamicArray<int> dArr1{ 1, 5, 6, 8 };
	REQUIRE(dArr1.getSize() == 4);
	REQUIRE(dArr1.getCapacity() == 4);

	dArr1.resize(10);
	REQUIRE(dArr1.getSize() == 10);
	REQUIRE(dArr1.getCapacity() == 10);
	REQUIRE(dArr1[0] == 1);
	REQUIRE(dArr1[1] == 5);
	REQUIRE(dArr1[2] == 6);
	REQUIRE(dArr1[3] == 8);

	dArr1.resize(5);
	REQUIRE(dArr1.getSize() == 5);
	REQUIRE(dArr1.getCapacity() == 10);
	REQUIRE(dArr1[0] == 1);
	REQUIRE(dArr1[1] == 5);
	REQUIRE(dArr1[2] == 6);
	REQUIRE(dArr1[3] == 8);

	dArr1.resize(2);
	REQUIRE(dArr1.getSize() == 2);
	REQUIRE(dArr1.getCapacity() == 10);
	REQUIRE(dArr1[0] == 1);
	REQUIRE(dArr1[1] == 5);

	dArr1.resize(7, 0);
	REQUIRE(dArr1.getSize() == 7);
	REQUIRE(dArr1.getCapacity() == 10);
	REQUIRE(dArr1[0] == 1);
	REQUIRE(dArr1[1] == 5);
	REQUIRE(dArr1[2] == 0);
	REQUIRE(dArr1[6] == 0);
}

TEST_CASE("Test Reserve") {

	DynamicArray<int> dArr1;

	dArr1.reserve(2);
	REQUIRE(dArr1.getCapacity() == 4);
	REQUIRE(dArr1.getSize() == 0);

	dArr1.reserve(15);
	REQUIRE(dArr1.getCapacity() == 15);
	REQUIRE(dArr1.getSize() == 0);

	dArr1.reserve(10);
	REQUIRE(dArr1.getCapacity() == 15);
	REQUIRE(dArr1.getSize() == 0);


	DynamicArray<int> dArr2{ 1, 5, 6, 8 };

	dArr2.reserve(8);
	REQUIRE(dArr2.getCapacity() == 8);
	REQUIRE(dArr2.getSize() == 4);

}

TEST_CASE("Test shrink_to_fit") {

	DynamicArray<int> dArr1;
	dArr1.shrink_to_fit();
	REQUIRE(dArr1.getCapacity() == 0);
	REQUIRE(dArr1.getSize() == 0);

	DynamicArray<int> dArr2{ 1, 5, 6, 8, 7 };
	dArr2.reserve(20);
	REQUIRE(dArr2.getCapacity() == 20);
	REQUIRE(dArr2.getSize() == 5);

	dArr2.shrink_to_fit();
	REQUIRE(dArr2.getCapacity() == 5);
	REQUIRE(dArr2.getSize() == 5);
	REQUIRE(dArr2[0] == 1);
	REQUIRE(dArr2[1] == 5);
	REQUIRE(dArr2[2] == 6);
	REQUIRE(dArr2[3] == 8);
	REQUIRE(dArr2[4] == 7);

}

TEST_CASE("Push_back & Pop_back") {

	DynamicArray<int> dArr1;

	REQUIRE(dArr1.empty() == true);
	REQUIRE_THROWS_AS(dArr1.pop_back(), std::logic_error);

	dArr1.push_back(3);
	REQUIRE(dArr1.getCapacity() == 4);
	REQUIRE(dArr1.getSize() == 1);
	REQUIRE(dArr1[0] == 3);
	REQUIRE(dArr1.empty() == false);

	dArr1.pop_back();
	REQUIRE(dArr1.getCapacity() == 4);
	REQUIRE(dArr1.getSize() == 0);
	REQUIRE(dArr1.empty() == true);

	dArr1.push_back(3);
	REQUIRE(dArr1.getCapacity() == 4);
	REQUIRE(dArr1.getSize() == 1);
	REQUIRE(dArr1[0] == 3);

	dArr1.push_back(5);
	REQUIRE(dArr1.getCapacity() == 4);
	REQUIRE(dArr1.getSize() == 2);
	REQUIRE(dArr1[1] == 5);

	dArr1.push_back(1);
	REQUIRE(dArr1.getCapacity() == 4);
	REQUIRE(dArr1.getSize() == 3);
	REQUIRE(dArr1[2] == 1);

	dArr1.push_back(6);
	REQUIRE(dArr1.getCapacity() == 4);
	REQUIRE(dArr1.getSize() == 4);
	REQUIRE(dArr1[3] == 6);

	dArr1.push_back(5);
	REQUIRE(dArr1.getCapacity() == 6);  // floor (1.6 * 4)
	REQUIRE(dArr1.getSize() == 5);
	REQUIRE(dArr1[4] == 5);

	dArr1.push_back(5);
	REQUIRE(dArr1.getCapacity() == 6);
	REQUIRE(dArr1.getSize() == 6);
	REQUIRE(dArr1[5] == 5);

	dArr1.pop_back();
	REQUIRE(dArr1.getCapacity() == 6);
	REQUIRE(dArr1.getSize() == 5);
	REQUIRE(dArr1[4] == 5);

	dArr1.push_back(0);
	REQUIRE(dArr1.getCapacity() == 6);
	REQUIRE(dArr1.getSize() == 6);
	REQUIRE(dArr1[5] == 0);

	dArr1.push_back(100);
	REQUIRE(dArr1.getCapacity() == 9); // floor (1.6 * 6)
	REQUIRE(dArr1.getSize() == 7);
	REQUIRE(dArr1[5] == 0);
	REQUIRE(dArr1[6] == 100);

	dArr1.pop_back();
	REQUIRE(dArr1.getCapacity() == 9);
	REQUIRE(dArr1.getSize() == 6);

	dArr1.reserve(10);
	REQUIRE(dArr1.getCapacity() == 10);
	REQUIRE(dArr1.getSize() == 6);

	dArr1.push_back(0);
	dArr1.push_back(1);
	dArr1.push_back(2);
	dArr1.push_back(3);
	REQUIRE(dArr1.getCapacity() == 10);
	REQUIRE(dArr1.getSize() == 10);
	REQUIRE(dArr1[9] == 3);

	dArr1.push_back(5);
	REQUIRE(dArr1.getCapacity() == 16);
	REQUIRE(dArr1.getSize() == 11);
	REQUIRE(dArr1[10] == 5);

	DynamicArray<int> dArr2 {3, 5, 7, 8};
	dArr2.push_back(1);
	REQUIRE(dArr2.getCapacity() == 6); // floor (1.6 * 4)
	REQUIRE(dArr2.getSize() == 5);
	REQUIRE(dArr2[4] == 1);


	DynamicArray<int> dArr3{ 3, 5, 7, 8, 1 };
	dArr3.push_back(2);
	REQUIRE(dArr3.getCapacity() == 8); // 1.6 * 5
	REQUIRE(dArr3.getSize() == 6);
	REQUIRE(dArr3[5] == 2);
}

TEST_CASE("Test Access methods") {

	DynamicArray<int> dArr1;
	dArr1.push_back(3);
	REQUIRE(dArr1.at(0) == 3);
	REQUIRE(dArr1.front() == 3);
	REQUIRE(dArr1.back() == 3);

	dArr1.push_back(4);
	REQUIRE(dArr1.at(1) == 4);
	REQUIRE(dArr1.front() == 3);
	REQUIRE(dArr1.back() == 4);

	dArr1.push_back(1);
	REQUIRE(dArr1.at(2) == 1);
	REQUIRE(dArr1.front() == 3);
	REQUIRE(dArr1.back() == 1);

	REQUIRE_THROWS_AS(dArr1.at(3), std::out_of_range);
	REQUIRE_THROWS_AS(dArr1.at(-1), std::out_of_range);
	
	dArr1.pop_back();
	REQUIRE(dArr1.front() == 3);
	REQUIRE(dArr1.back() == 4);
	REQUIRE_THROWS_AS(dArr1.at(2), std::out_of_range);

	dArr1.push_back(100);
	REQUIRE(dArr1.at(2) == 100);
	REQUIRE(dArr1.front() == 3);
	REQUIRE(dArr1.back() == 100);
}