#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "DynamicArray.h"

#include <vector>

void requireSameContents(DynamicArray<int>& dArr, std::vector<int> expected)
{
	for (size_t i = 0; i < dArr.getSize(); ++i)
		REQUIRE(dArr[i] == expected[i]);
}

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
	SECTION("empty() returns true")
	{
		REQUIRE(dArr.empty() == true);
	}
}

TEST_CASE("Initialization list constructed object has correct properties")
{
	DynamicArray<int> dArr{ 4, 5, 6, 8 };

	SECTION("getSize() returns 4")
	{
		REQUIRE(dArr.getSize() == 4);
	}
	SECTION("getCapacity() returns 4")
	{
		REQUIRE(dArr.getCapacity() == 4);
	}
	SECTION("empty() returns false")
	{
		REQUIRE(dArr.empty() == false);
	}
	SECTION("Elements are stored correctly")
	{
		std::vector<int> expected{ 4, 5, 6, 8 };
		requireSameContents(dArr, expected);
	}
}

TEST_CASE("Copy-constructed dynamic array has correct properties")
{
	DynamicArray<int> original{ 4, 5, 6, 8 };
	DynamicArray<int> copy(original);

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
		std::vector<int> expected{ 4, 5, 6, 8 };
		requireSameContents(copy, expected);
	}
}

TEST_CASE("Dynamic array constructed with specific size has correct properties") {
	DynamicArray<int> dArr(10);
	REQUIRE(dArr.getSize() == 0);
	REQUIRE(dArr.getCapacity() == 10);
}

TEST_CASE("DynamicArray::resize()") {
	
	DynamicArray<int> dArr{ 1, 5, 6, 8 };
	std::vector<int> expected{ 1, 5, 6, 8 };

	SECTION("Resizing with the same size as the current size doesn't change anything")
	{
		dArr.resize(4);
		REQUIRE(dArr.getSize() == 4);
		REQUIRE(dArr.getCapacity() == 4);
		requireSameContents(dArr, expected);
	}

	SECTION("Resizing with less size than the current size cuts elements but doesn't change capacity")
	{
		dArr.resize(2);
		REQUIRE(dArr.getSize() == 2);
		REQUIRE(dArr.getCapacity() == 4);
		requireSameContents(dArr, expected);
	}

	SECTION("Resizing with more size than the current capacity increases the capacity")
	{
		dArr.resize(10);
		REQUIRE(dArr.getSize() == 10);
		REQUIRE(dArr.getCapacity() == 10);
	}

	SECTION("Resizing with given value and more size than the current capacity increases the capacity and creates new elements with that value")
	{
		std::vector<int> expected2{ 1, 5, 6, 8, 2, 2, 2 };
		dArr.resize(7, 2);
		REQUIRE(dArr.getSize() == 7);
		REQUIRE(dArr.getCapacity() == 7);
		requireSameContents(dArr, expected2);
	}
}

TEST_CASE("DynamicArray::reserve()") {

	DynamicArray<int> dArr;

	SECTION("reserve() allocates not less than the initial capacity and doesn't change the size")
	{
		dArr.reserve(2);
		REQUIRE(dArr.getCapacity() == dArr.getInitCap());
		REQUIRE(dArr.getSize() == 0);
	}

	DynamicArray<int> dArr2{ 1 , 5, 6, 8 };
	std::vector<int> v{ 1 , 5, 6, 8 };

	SECTION("Reserving less than the current capacity doesn't change anything")
	{
		dArr2.reserve(2);
		REQUIRE(dArr2.getCapacity() == 4);
		REQUIRE(dArr2.getSize() == 4);
		requireSameContents(dArr2, v);
	}

	SECTION("Consecutive reservings don't change the size and the elements")
	{
		dArr2.reserve(2);
		dArr2.reserve(8);
		dArr2.reserve(17);
		dArr2.reserve(6);
		dArr2.reserve(9);

		REQUIRE(dArr2.getCapacity() == 17);
		REQUIRE(dArr2.getSize() == 4);
		requireSameContents(dArr2, v);
	}
}

TEST_CASE("DynamicArray::shrink_to_fit()") {

	DynamicArray<int> dArr{ 1, 5, 6, 8, 7 };
	std::vector<int> expected{ 1, 5, 6, 8, 7 };
	SECTION("shrink_to_fit() doesn't do anything if size is equal to the capacity")
	{
		REQUIRE(dArr.getCapacity() == 5);
		REQUIRE(dArr.getSize() == 5);

		dArr.shrink_to_fit();
		REQUIRE(dArr.getCapacity() == 5);
		REQUIRE(dArr.getSize() == 5);

		requireSameContents(dArr, expected);
	}

	SECTION("shrink_to_fit() limits the capacity to the size if the capacity is more than the size")
	{
		dArr.reserve(100);
		REQUIRE(dArr.getCapacity() == 100);
		REQUIRE(dArr.getSize() == 5);

		dArr.shrink_to_fit();
		REQUIRE(dArr.getCapacity() == 5);
		REQUIRE(dArr.getSize() == 5);

		requireSameContents(dArr, expected);
	}
}

TEST_CASE("DynamicArray::push_back()") {

	DynamicArray<int> dArr;
	std::vector<int> expected;
	dArr.push_back(3);
	expected.push_back(3);

	SECTION("push_back() on empty DynArr initializes it with the class's initial capacity")
	{
		REQUIRE(dArr.getCapacity() == dArr.getInitCap());
		REQUIRE(dArr.getSize() == 1);
	}

	dArr.push_back(2);
	expected.push_back(2);
	dArr.push_back(1);
	expected.push_back(1);
	dArr.push_back(5);
	expected.push_back(5);

	SECTION("push_back() doesn't change the capacity if it is more than the size")
	{
		REQUIRE(dArr.getCapacity() == 4);
		REQUIRE(dArr.getSize() == 4);
	}

	SECTION("push_back() adds elements correctly")
	{
		requireSameContents(dArr, expected);
	}

	SECTION("push_back() increases capacity correctly")
	{
		size_t currentCap = dArr.getCapacity();
		dArr.push_back(0);
		expected.push_back(0);

		REQUIRE(dArr.getCapacity() == std::floor(dArr.getResizeFactor() * currentCap));
		REQUIRE(dArr.getSize() == 5);
		requireSameContents(dArr, expected);
	}
}

TEST_CASE("DynamicArray::pop_back()")
{
	DynamicArray<int> dArr;
	std::vector<int> expected;

	SECTION("pop_back() on empty array throws exception")
	{
		REQUIRE_THROWS_AS(dArr.pop_back(), std::logic_error);
	}

	dArr.push_back(2);
	expected.push_back(2);
	dArr.push_back(5);
	expected.push_back(5);

	SECTION("pop_back() reduces the size but doesn't affect the capacity")
	{
		dArr.pop_back();
		expected.pop_back();
		REQUIRE(dArr.getCapacity() == 4);
		REQUIRE(dArr.getSize() == 1);
		requireSameContents(dArr, expected);

		dArr.pop_back();
		expected.pop_back();
		REQUIRE(dArr.getCapacity() == 4);
		REQUIRE(dArr.getSize() == 0);
		requireSameContents(dArr, expected);
	}
}

TEST_CASE("Test Access methods") {

	DynamicArray<int> dArr{ 4, 5, 6, 8 };
	std::vector<int> expected{ 4, 5, 6, 8 };

	SECTION("at() returns the elements correctly")
	{		
		for (size_t i = 0; i < expected.size(); ++i)
			REQUIRE(dArr.at(i) == expected.at(i));
	}

	SECTION("at() throws an exception when the index is out of range")
	{
		REQUIRE_THROWS_AS(dArr.at(4), std::out_of_range);
		REQUIRE_THROWS_AS(dArr.at(-1), std::out_of_range);
	}

	SECTION("front() returns the correct element")
	{
		REQUIRE(dArr.front() == expected.front());

		dArr.pop_back();
		dArr.resize(2);
		dArr.push_back(11);

		REQUIRE(dArr.front() == expected.front());
	}

	SECTION("back() returns the correct element")
	{
		REQUIRE(dArr.back() == expected.back());

		dArr.pop_back();
		expected.pop_back();
		dArr.resize(2);
		expected.resize(2);
		dArr.push_back(11);
		expected.push_back(11);

		REQUIRE(dArr.back() == expected.back());
	}
}