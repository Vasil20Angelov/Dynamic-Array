#pragma once
#include <exception>

template <class T>
class Container {

private:
	static constexpr size_t INITIAL_CAPACITY = 4;

public:

	Container() : data(nullptr), capacity(0) {}

	Container(size_t size) {
		capacity = size < INITIAL_CAPACITY ? INITIAL_CAPACITY : size;
		data = new T[capacity];
	}

	Container(const Container& other, size_t size) : Container(size) {

		for (int i = 0; i < size; ++i)
			data[i] = other[i];
	}

	~Container() {
		clear();
	}


	inline const T& operator[](size_t index) const { return data[index]; }
	inline T& operator[](size_t index) { return const_cast<T&>(const_cast<const Container&>(*this)[index]); }

	inline size_t getCap() const { return capacity; }
	inline size_t getInitCap() const { return INITIAL_CAPACITY; }

	inline void swap(Container& other) {
		std::swap(data, other.data);
		capacity = other.capacity;
	}
	
	inline void reserve(size_t curSize, size_t wantedSize) {
		if (wantedSize > capacity) {
			if (wantedSize < INITIAL_CAPACITY)
				wantedSize = INITIAL_CAPACITY;
			T* temp = nullptr;
			try {
				temp = new T[wantedSize];
				for (int i = 0; i < curSize; ++i)
					temp[i] = data[i];
			}
			catch (std::exception& e) {
				throw e;
			}

			capacity = wantedSize;
			std::swap(temp, data);
			delete[] temp;
		}
	}

	inline void clear() {
		if (data)
			delete[] data;
		capacity = 0;
	}

private:

	T* data;
	size_t capacity;
};