#include "DynamicArray.h"

template<class T>
inline DynamicArray<T>::DynamicArray() : data(), size(0)
{
}

template<class T>
inline DynamicArray<T>::DynamicArray(size_t newSize) : data(newSize), size(0)
{
}

template<class T>
inline DynamicArray<T>::DynamicArray(const DynamicArray& other)
{
	copy(other);
}

template<class T>
inline DynamicArray<T>::DynamicArray(const std::initializer_list<T>& lst)
{
	size_t capacity = lst.size() > data.getInitCap() ? lst.size() : data.getInitCap();
	
	data.reserve(0, capacity);

	size_t i = 0;
	for (const T& element : lst)
	{
		data[i] = element;
		++i;
	}

	size = lst.size();
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
	return const_cast<T&>(const_cast<const DynamicArray&>(*this)[position]);
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
	return const_cast<T&>(const_cast<const DynamicArray&>(*this).at(position));
}

template<class T>
inline const T& DynamicArray<T>::front() const
{
	return data[0];
}

template<class T>
inline T& DynamicArray<T>::front()
{
	return const_cast<T&>(const_cast<const DynamicArray&>(*this).front());
}

template<class T>
inline const T& DynamicArray<T>::back() const
{
	return data[size - 1];
}

template<class T>
inline T& DynamicArray<T>::back()
{
	return const_cast<T&>(const_cast<const DynamicArray&>(*this).back());
}

template<class T>
inline void DynamicArray<T>::push_back(const T& element)
{
	if (size == data.getCap()) {

		size_t newCapacity = (size_t)(data.getCap() * RESIZE_FACTOR);
		if (newCapacity < data.getInitCap())
			newCapacity = data.getInitCap();

		data.reserve(size, newCapacity);
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
	data.reserve(oldSize, newSize);
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
	data.reserve(size, newCapacity);
}

template<class T>
inline void DynamicArray<T>::shrink_to_fit()
{
	if (size == data.getCap())
		return;

	if (size == 0) {
		data.clear();
		return;
	}

	Container<T> temp(data, size);
	data.swap(temp);
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
	return data.getCap();
}

template<class T>
inline size_t DynamicArray<T>::getInitCap() const
{
	return data.getInitCap();
}

template<class T>
inline float DynamicArray<T>::getResizeFactor() const
{
	return RESIZE_FACTOR;
}

template<class T>
inline void DynamicArray<T>::copy(const DynamicArray<T>& other)
{
	if (data.getCap() < other.size) {
		data.clear();

		data.reserve(0, other.size);
	}

	for (int i = 0; i < other.size; ++i) {
		data[i] = other.data[i];
	}

	size = other.size;
}

template<class T>
inline void DynamicArray<T>::clear()
{
	size = 0;
	data.clear();
}