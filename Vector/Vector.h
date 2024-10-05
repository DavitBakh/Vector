// Create a custom vector class that would support all the functionality
// given in main.cpp.

// Again: Declare your functions inside your class, but define them outside of it.
#include <cstddef>

template <typename T>
class Vector
{
private:
	size_t _size;
	size_t _capacity;
	T* _arr;

public:
	Vector(size_t size = 0, T defaultValue = 0);
	size_t size() const;
	~Vector();

};

template <typename T>
Vector<T>::Vector(size_t size, T defaultValue) : _size(size), _capacity(size), _arr(new T[size]) 
{
	for (size_t i = 0; i < _size; i++)
		_arr[i] = defaultValue;
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
