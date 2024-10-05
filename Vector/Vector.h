#pragma once

#include <cstddef>
#include <initializer_list>
#include <cassert>
#include <stdexcept>

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
	~Vector();



	size_t size() const;
	size_t capacity() const;
	void push_back(const T& val);
	void pop_back();
	void resize(size_t newSize);
	void clear();
	bool empty() const;
	void reserve(size_t newCapacity);
	void shrink_to_fit();

	T& at(size_t index);
	const T& at(size_t index) const;
	T& front();
	const T& front() const;
	T& back();
	const T& back() const;
	T* data();
	const T* data() const;



	T& operator[](size_t index);
	const T& operator[](size_t index) const;
	Vector<T>& operator=(const Vector<T>& source);

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

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& source)
{
	if (source != *this)
	{
		this->_capacity = source._capacity;
		this->_size = source._size;

		delete[] this->_arr;
		this->_arr = new T[_size];

		for (size_t i = 0; i < _size; i++)
			this->_arr[i] = source._arr[i];
	}

	return *this;
}

#pragma endregion

#pragma region TempRegin



template <typename T>
size_t Vector<T>::size() const
{
	return _size;
}

template<typename T>
size_t Vector<T>::capacity() const
{
	return _capacity;
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
bool Vector<T>::empty() const
{
	return _size == 0;
}

template<typename T>
void Vector<T>::clear()
{
	_size = 0;
}

template<typename T>
void Vector<T>::reserve(size_t newCapacity)
{
	if (newCapacity > _capacity)
		_capacity = newCapacity;
}

template<typename T>
void Vector<T>::shrink_to_fit()
{
	_capacity = _size;
}


#pragma endregion

#pragma region AccessFunctions

template<typename T>
T& Vector<T>::at(size_t index)
{
	if (index >= _size)
		throw std::invalid_argument("Index out of range");

	return _arr[index];
}

template<typename T>
const T& Vector<T>::at(size_t index) const
{
	if (index >= _size)
		throw std::invalid_argument("Index out of range");

	return _arr[index];
}

template<typename T>
T& Vector<T>::front()
{
	return _arr[0];
}

template<typename T>
const T& Vector<T>::front() const
{
	return _arr[0];
}
template<typename T>
T& Vector<T>::back()
{
	return _arr[_size - 1];
}

template<typename T>
const T& Vector<T>::back() const
{
	return _arr[_size - 1];
}

template<typename T>
T* Vector<T>::data()
{
	return _arr;
}

template<typename T>
const T* Vector<T>::data() const
{
	return _arr;
}
#pragma endregion

