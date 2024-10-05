#pragma once

#include <cstddef>
#include <initializer_list>
#include <cassert>

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
	Vector(const Vector& other);


	size_t size() const;
	~Vector();

	T& operator[](size_t index);
	const T& operator[](size_t index) const;


	void push_back(const T& val);
	void pop_back();
	void resize(size_t newSize);
	void clear();
	bool empty();

	template <typename U>
	friend bool operator==(const Vector<U>& lhs, const Vector<U>& rhs);

};

#pragma region Ctors and Destructor

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

template<typename T>
Vector<T>::Vector(const Vector& other)
{
	this->_size = other._size;
	this->_capacity = other._capacity;

	this->_arr = new T[_size];
	for (size_t i = 0; i < _size; i++)
		this->_arr[i] = other._arr[i];
}

template <typename T>
Vector<T>::~Vector()
{
	delete[] _arr;
}

#pragma endregion

#pragma region Operators

template <typename T>
T& Vector<T>::operator[](size_t index)
{
	assert(index < _size);

	return _arr[index];
}

template<typename T>
const T& Vector<T>::operator[](size_t index) const
{
	assert(index < _size);

	return _arr[index];
}

template<typename T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs)
{
	if (lhs.size() != rhs.size())
		return false;

	for (size_t i = 0; i < lhs.size(); i++)
		if (lhs._arr[i] != rhs._arr[i])
			return false;

	return true;
}

template<typename T>
bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs)
{
	return !(lhs == rhs);
}

#pragma endregion



#pragma region TempRegin



template <typename T>
size_t Vector<T>::size() const
{
	return _size;
}


template<typename T>
void Vector<T>::push_back(const T& val)
{
	if (_size == _capacity)
		resize(2 * _capacity + 1);

	_arr[_size++] = val;
}

template<typename T>
void Vector<T>::pop_back()
{
	_size--;
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

template<typename T>
bool Vector<T>::empty()
{
	return _size == 0;
}

template<typename T>
void Vector<T>::clear()
{
	_size = 0;
}

#pragma endregion





