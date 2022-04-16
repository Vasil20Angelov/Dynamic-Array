#pragma once
#include <initializer_list>
#include <stdexcept>
#include "Container.h"

template <class T>
class DynamicArray
{
private:
	static constexpr float RESIZE_FACTOR = 1.6f;

public:

	//! Default constructor
	DynamicArray();
	//! Constructs the object by allocating memory
	DynamicArray(size_t newSize);
	//! Copy constructor
	DynamicArray(const DynamicArray<T>& other);
	//! Constructs the object by the elements of a given initializer list
	DynamicArray(const std::initializer_list<T>& lst);
	
	//! Operator =
	DynamicArray& operator=(const DynamicArray<T>& other);

	/**
	* \brief Access an element at given position
	*
	* By given position returns a const reference to the element at that position
	* If the position is invalid, the behaviour is undefined
	*/
	const T& operator[](size_t position) const;

	/**
	* \brief Access an element at given position
	*
	* By given position returns a reference to the element at that position
	* If the position is invalid, the behaviour is undefined
	*/
	T& operator[](size_t position);

	/**
	* \brief Access an element at given position
	* 
	* By given position returns a const reference to the element at that position
	* If the position is invalid, throws an out_of_range exception
	*/
	const T& at(size_t position) const;

	/**
	* \brief Access an element at given position
	*
	* By given position returns a reference to the element at that position
	* If the position is invalid, throws an out_of_range exception
	*/
	T& at(size_t position);

	/**
	* \brief Access the first element
	* 
	* Returns a const reference to the element at index 0
	* If the array is empty, the behaviour is undefined
	*/
	const T& front() const;

	/**
	* \brief Access the first element
	*
	* Returns a reference to the element at index 0
	* If the array is empty, the behaviour is undefined
	*/
	T& front();


	/**
	* \brief Access the last element
	* 
	* Returns a const reference to the element at index size - 1
	* If the array is empty, the behaviour is undefined
	*/
	const T& back() const;

	/**
	* \brief Access the last element
	*
	* Returns a reference to the element at index size - 1
	* If the array is empty, the behaviour is undefined
	*/
	T& back();

	/**
	* \brief Add an element
	* 
	* Adds an element on the back of the array.
	* If the array is full then it's capacity is increased. Otherwise an element is just added at position size for O(1) time.
	*/
	void push_back(const T& element);

	/**
	* \brief Remove an element
	* 
	* Removes the element at the last position.
	* The element is not actually deleted. Only the size of the array is decreased.
	* Using push_back() after pop_back() will lead to overwriting the element of the last position.
	* Trying to execute the method on empty array will throw an exception
	*/
	void pop_back();

	/**
	* \brief Resize the array
	* 
	* Changes the size of the array to the given one.
	* If the current and the wanted size are the same, the method does nothing.
	* If the current size is less than the wanted size, it is being increased.
	* If the capacity is also less than than the wanted size, the capacity is also being increased.
	* The value of the new elements is undefined.
	* If the current size is more than the wanted size then the size is decreased but the elements are not deleted.
	*/
	void resize(size_t newSize);

	/**
	* \brief Resize the array
	*
	* Changes the size of the array to the given one.
	* If the current and the wanted size are the same, the method does nothing.
	* If the current size is less than the wanted size, it is being increased.
	* If the capacity is also less than than the wanted size, the capacity is also being increased.
	* The new elements are given the value of the second argument of the method.
	* If the current size is more than the wanted size then the size is decreased but the elements are not deleted.
	*/
	void resize(size_t newSize, const T& value);


	/**
	* \brief Reserve extra space
	* 
	* Changes the capacity of the array to the given one, only if it is greater than the current one.
	* Otherwise it does nothing.
	* The elements and the size of the array are not touched.
	*/
	void reserve(size_t newCapacity);

	/**
	* \brief Reduce the capacity
	* 
	* If the capacity is more than the size of the array, the capacity is changed to the value of the size.
	*/
	void shrink_to_fit();

	/**
	* \brief Check if the array is empty
	* 
	*  \return True if size = 0
	*  \return False if size != 0
	*/
	bool empty() const;

	//! Return size
	size_t getSize() const;
	//! Return capacity
	size_t getCapacity() const;

	//! Return the initial capacity value 
	size_t getInitCap() const;
	//! Return the resizing factor value
	float getResizeFactor() const;

private:

	//! Copies the data of other object
	void copy(const DynamicArray<T>& other);
	//! Free allocated memory and zeroes class members
	void clear();


	// Class members:
	
	Container<T> data;
	size_t size; //!< Number of elements stored in the array
};

#include "DynamicArray.ipp"
