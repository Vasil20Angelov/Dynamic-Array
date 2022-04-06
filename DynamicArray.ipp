#include "DynamicArray.h"

template<class T>
inline DynamicArray<T>::DynamicArray() : data(nullptr), size(0), capacity(0)
{
}

template<class T>
inline DynamicArray<T>::DynamicArray(size_t newSize)
{
	capacity = newSize > INITIAL_CAPACITY ? newSize : INITIAL_CAPACITY;
	data = new T[capacity];
	size = 0;
}

template<class T>
inline DynamicArray<T>::DynamicArray(const DynamicArray& other)
{
	copy(other);
}

template<class T>
inline DynamicArray<T>::DynamicArray(const std::initializer_list<T>& lst)
{
	size = lst.size();
	capacity = size > INITIAL_CAPACITY ? size : INITIAL_CAPACITY;

	try {
		data = new T[capacity];
		size_t i = 0;
		for (const T& element : lst)
		{
			data[i] = element;
			++i;
		}
	}
	catch (std::exception& e) {
		clear();
		throw e;
	}
}

template<class T>
inline DynamicArray<T>::~DynamicArray()
{
	clear();
}

template<class T>
inline DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other)
{
	if (this != &other) {
		copy(other);
	}

	return *this;
}

template<class T>
inline const T& DynamicArray<T>::operator[](size_t position) const
{
	return data[position];
}

template<class T>
inline T& DynamicArray<T>::operator[](size_t position)
{
	return const_cast<T&>(static_cast<const DynamicArray&>(*this)[position]);
}

template<class T>
inline const T& DynamicArray<T>::at(size_t position) const
{
	if (size <= position || position < 0)
		throw std::out_of_range("Out of range\n");

	return data[position];
}

template<class T>
inline T& DynamicArray<T>::at(size_t position)
{
	return const_cast<T&>(static_cast<const DynamicArray&>(*this).at(position));
}

template<class T>
inline const T& DynamicArray<T>::front() const
{
	return data[0];
}

template<class T>
inline T& DynamicArray<T>::front()
{
	return const_cast<T&>(static_cast<const DynamicArray&>(*this).front());
}

template<class T>
inline const T& DynamicArray<T>::back() const
{
	return data[size - 1];
}

template<class T>
inline T& DynamicArray<T>::back()
{
	return const_cast<T&>(static_cast<const DynamicArray&>(*this).back());
}

template<class T>
inline void DynamicArray<T>::push_back(const T& element)
{
	if (size == capacity) {

		size_t newCapacity = (size_t)std::floor(capacity * RESIZE_FACTOR);
		if (newCapacity < INITIAL_CAPACITY)
			newCapacity = INITIAL_CAPACITY;

		increase_capacity(newCapacity);
	}

	data[size] = element;
	++size;
}

template<class T>
inline void DynamicArray<T>::pop_back()
{
	if (empty())
		throw std::logic_error("Pop from empty array\n");
	--size;
}

template<class T>
inline void DynamicArray<T>::resize(size_t newSize)
{
	if (newSize == size)
		return;

	size_t oldSize = size;
	size = newSize;

	// If newSize is less than the current capacity, it does nothing
	increase_capacity(newSize);
}

template<class T>
inline void DynamicArray<T>::resize(size_t newSize, const T& value)
{
	size_t oldSize = size;
	resize(newSize);

	if (oldSize < size) {
		for (size_t i = oldSize; i < size; ++i)
			data[i] = value;
	}
}

template<class T>
inline void DynamicArray<T>::reserve(size_t newCapacity)
{
	increase_capacity(newCapacity);
}

template<class T>
inline void DynamicArray<T>::shrink_to_fit()
{
	if (size == capacity)
		return;

	if (size == 0) {
		clear();
		return;
	}

	T* temp = nullptr;
	try {
		temp = new T[size];
		for (int i = 0; i < size; ++i)
			temp[i] = data[i];

		delete[] data;
		data = new T[size];

		for (int i = 0; i < size; ++i)
			data[i] = temp[i];

		capacity = size;
		delete[] temp;
	}
	catch (std::exception& e) {

		if (temp)
			delete[] temp;
		clear();
		throw e;
	}
}

template<class T>
inline bool DynamicArray<T>::empty() const
{
	return size == 0;
}

template<class T>
inline size_t DynamicArray<T>::getSize() const
{
	return size;
}

template<class T>
inline size_t DynamicArray<T>::getCapacity() const
{
	return capacity;
}

template<class T>
inline void DynamicArray<T>::increase_capacity(size_t newCapacity)
{
	if (capacity < newCapacity) {
		T* temp = nullptr;
		try {
			temp = new T[size];
			for (int i = 0; i < size; ++i)
				temp[i] = data[i];
		}
		catch (std::exception& e) {
			delete[] temp;
			throw e;
		}

		delete[] data;

		capacity = newCapacity > INITIAL_CAPACITY ? newCapacity : INITIAL_CAPACITY;
		try {
			data = new T[capacity];
			for (int i = 0; i < size; ++i)
				data[i] = temp[i];

			delete[] temp;
		}
		catch (std::exception& e) {
			delete[] temp;
			clear();
			throw e;
		}
	}
}

template<class T>
inline void DynamicArray<T>::copy(const DynamicArray<T>& other)
{
	try {
		if (capacity < other.size) {
			if (data) {
				delete[] data;
			}

			data = new T[other.size];
			capacity = other.size;
		}
		
		for (int i = 0; i < other.size; ++i) {
			data[i] = other.data[i];
		}

		size = other.size;
	}
	catch (std::exception& e) {
		clear();
		throw e;
	}
}

template<class T>
inline void DynamicArray<T>::clear()
{
	size = 0;
	capacity = 0;

	if (data) {
		delete[] data;
		data = nullptr;
	}
}

