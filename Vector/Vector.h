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
	Vector(size_t size = 0);
	Vector(size_t size, const T& val);
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
	void swap(Vector& other);

	template <typename... Args>
	void emplace_back(Args&&... args);

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
Vector<T>::Vector(size_t size) : _size(size), _capacity(size), _arr(reinterpret_cast<T*>(new char[size * sizeof(T)] {})) { }

template<typename T>
Vector<T>::Vector(size_t size, const T& val) : Vector(size)
{
	for (size_t i = 0; i < size; i++)
		_arr[i] = val;
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> initList) : _size(initList.size()), _capacity(initList.size()), _arr(new T[initList.size()])
{
	for (auto iter = initList.begin(); iter != initList.end(); ++iter)
		_arr[iter - initList.begin()] = *iter;
}

template<typename T>
Vector<T>::Vector(const Vector& other) : _size(other._size), _capacity(other._capacity), _arr(reinterpret_cast<T*>(new char[_capacity * sizeof(T)]))
{
	for (size_t i = 0; i < _size; i++)
		_arr[i] = other._arr[i];
}

template <typename T>
Vector<T>::~Vector()
{
	for (int i = 0; i < _size; i++)
		_arr[i].~T();

	delete[] reinterpret_cast<char*>(_arr);
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
		this->~Vector();

		this->_capacity = source._capacity;
		this->_size = source._size;


		this->_arr = reinterpret_cast<T*>(new char[_capacity * sizeof(T)] {});
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
	_arr[--_size].~T();
}

template<typename T>
void Vector<T>::resize(size_t newSize)
{
	T* temp = reinterpret_cast<T*>(new char[newSize * sizeof(T)] {});

	//hnaravora aveli chisht kliner this->~Vector() kanchel, 
	//vorpisi kodi krknutyun chlini ev logikan mi texum kentronacac lini SOLID-i hamadzayn, bayc senc aveli arag klini
	//kareli e qnnutyan jamanak qnnarkel
	if (_size > newSize)
	{
		for (size_t i = newSize; i < _size; i++)
			_arr[i].~T();

		_size = newSize;
	}
	_capacity = newSize;

	for (size_t i = 0; i < _size; i++)
	{
		temp[i] = _arr[i];
		_arr[i].~T();
	}

	delete[] reinterpret_cast<char*>(_arr);
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
	for (size_t i = 0; i < _size; i++)
		_arr[i].~T();

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

template<typename T>
void Vector<T>::swap(Vector& other)
{
	T* temp = this->_arr;
	this->_arr = other._arr;
	other._arr = temp;

	std::swap(this->_size, other._size);
	std::swap(this->_capacity, other._capacity);
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

template<typename T>
template<typename ...Args>
void Vector<T>::emplace_back(Args && ...args)
{
	push_back(T(std::forward<Args>(args)...));
}