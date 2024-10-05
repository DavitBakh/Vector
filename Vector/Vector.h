#pragma once
// Create a custom vector class that would support all the functionality
// given in main.cpp.

// Again: Declare your functions inside your class, but define them outside of it.
#include <cstddef>
#include <initializer_list>

template <typename T>
class Vector
{
private:
	size_t _size;
	size_t _capacity;
	T* _arr;

public:
	Vector(size_t size = 0, T defaultValue = 0);
	Vector(std::initializer_list<T> initList);
	size_t size() const;
	~Vector();

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	void push_back(const T& val);
	void resize(size_t newSize);


};

template <typename T>
Vector<T>::Vector(size_t size, T defaultValue) : _size(size), _capacity(size), _arr(new T[size])
{
	for (size_t i = 0; i < _size; i++)
		_arr[i] = defaultValue;
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> initList) : _size(initList.size()), _capacity(initList.size()), _arr(new T[initList.size()])
{

	for (auto iter = initList.begin(); iter != initList.end(); ++iter)
		_arr[iter - initList.begin()] = *iter;
}

template <typename T>
size_t Vector<T>::size() const
{
	return _size;
}

template <typename T>
Vector<T>::~Vector()
{
	delete[] _arr;
}

template <typename T>
T& Vector<T>::operator[](size_t index)
{
	return _arr[index];
}

template<typename T>
const T& Vector<T>::operator[](size_t index) const
{
	return _arr[index];
}

template<typename T>
void Vector<T>::push_back(const T& val)
{
	if (_size == _capacity)
		resize(2 * _capacity + 1);

	_arr[_size++] = val;
}

template<typename T>
void Vector<T>::resize(size_t newSize)
{
	_capacity = newSize;

	if (_size > newSize)
		_size = newSize;

	T* temp = new T[newSize];

	for (size_t i = 0; i < _size; i++)
		temp[i] = _arr[i];

	delete[] _arr;
	_arr = temp;
}