#include "stdafx.h"
#pragma once

struct IndexOutOfRange
{
	std::string message;
	IndexOutOfRange(const char* cmessage) 
	{
		message = cmessage;
	}
};

struct SizeDifference
{
	std::string message;
	SizeDifference(const char* cmessage)
	{
		message = cmessage;
	}
};

struct VectorNullPtr
{
	std::string message;
	VectorNullPtr(const char* cmessage) 
	{
		message = cmessage;
	}
};

template <typename Type>
class Vector 
{
private:
	Type * arr;
	size_t size;
	size_t capacity;
	static const size_t MAXSIZE = 1024;
public:	
	explicit Vector(); // по умолчанию  
	explicit Vector(const size_t n); // размеру
	explicit Vector(const size_t n, const Type value); // по размеру и типом value (инициальизируются элементы этим типом)
	explicit Vector(const size_t n, const size_t m, const Type value); // задает зарезервированную память по умолчанию
	Vector(const Vector <Type> &vector); // конструктор копирования
	Vector(Vector <Type> &&vector); // конструктор перемещения

	inline Type& operator[](const size_t index);
	Vector<Type> &operator=(const Vector<Type> &vector); // оператор присваивания
	Vector<Type> &operator=(Vector<Type> &&vector); // перемещение

	template <typename Type> friend bool operator==(const Vector<Type> &leftVector, const Vector<Type> &rightVector);
	template <typename Type> friend bool operator!=(const Vector<Type> &leftVector, const Vector<Type> &rightVector);
	template <typename Type> friend bool operator< (const Vector<Type> &leftVector, const Vector<Type> &rightVector);
	template <typename Type> friend bool operator<=(const Vector<Type> &leftVector, const Vector<Type> &rightVector);
	template <typename Type> friend bool operator> (const Vector<Type> &leftVector, const Vector<Type> &rightVector);
	template <typename Type> friend bool operator>=(const Vector<Type> &leftVector, const Vector<Type> &rightVector);

	template <typename T> friend Vector<T> operator+(const Vector<T> &leftVector, const Vector<T> &rightVector);
	template <typename T> friend ostream &operator<<(ostream &stream, const Vector<T> &vector);
	template <typename T> friend istream &operator>>(istream &stream, const Vector<T> &vector);
	
	void reserve(size_t n); // резервирует память
	void resize(const size_t newSize); // меняет размер вектора
	void output();		
	void pushback(const Type element); // добавить в конец елемент типа Type
	Type popback(); // удаляет и возвращает последний элемент

	size_t getSize() const		{ return size; }
	size_t getCapacity() const	{ return capacity; }
	size_t getMAXSIZE() const	{ return MAXSIZE; }
	~Vector();
};


// по умолчанию
template <typename Type>
Vector<Type>::Vector()
{
	size = 1;
	capacity = 0;
	arr = new Type[size + capacity];
	arr[size - 1] = size;
}

// размеру
template <typename Type>
Vector<Type>::Vector(const size_t n)
{
	if (n > MAXSIZE) {
		throw IndexOutOfRange("too large size n");
	}
	size = n;
	capacity = 0;
	arr = new Type[size + capacity];
	for (size_t i = 0; i < size; i++)
	{
		arr[i] = i * i;
	}
}

// по размеру и типом value (инициальизируются элементы этим типом)
template <typename Type>
Vector<Type>::Vector(const size_t n, const Type value)
{
	if (n > MAXSIZE) {
		throw IndexOutOfRange("too large size n");
	}
	size = n;
	capacity = 0;
	arr = new Type[size + capacity];
	for (size_t i = 0; i < size; i++)
	{
		arr[i] = value;
	}
}

// задает зарезервированную память по умолчанию
template <typename Type>
Vector<Type>::Vector(const size_t n, const size_t m, const Type value)
{
	if (n > MAXSIZE) {
		throw IndexOutOfRange("too large size n");
	}
	size = n;
	capacity = m;
	arr = new Type[size + capacity];
	for (size_t i = 0; i < size; i++)
	{
		arr[i] = value;
	}
}

// конструктор копирования
template <typename Type>
Vector<Type>::Vector(const Vector <Type> &vector) 
{
	size = vector.size;
	capacity = vector.capacity;
	arr = new Type[size + capacity];
	for (size_t i = 0; i < size; i++)
	{
		arr[i] = vector.arr[i];
	}
}

// конструктор перемещения
template <typename Type>
Vector<Type>::Vector(Vector <Type> &&vector) 
{
	size = vector.size;
	capacity = vector.capacity;
	arr = vector.arr;
	vector.size = 0;
	vector.capacity = 0;
	vector.arr = nullptr;
}

template <typename Type>
inline Type& Vector<Type>::operator[](const size_t index)
{
	if (index >= size) {
		throw IndexOutOfRange("index out of range");
	}
	return arr[index];
}

// оператор присваивания
template <typename Type>
Vector<Type>& Vector<Type>::operator=(const Vector<Type> &vector)
{
	if (this == &vector)
	{
		return *this;
	}
	delete[]arr;
	size = vector.size;
	capacity = vector.capacity;
	arr = new Type[size + capacity];
	for (size_t i = 0; i < size; i++)
	{
		arr[i] = vector.arr[i];
	}
	return *this;
}

template <typename Type>
Vector<Type>& Vector<Type>::operator=(Vector<Type> &&vector)
{
	if (this == &vector)
	{
		return *this;
	}
	delete[]arr;
	size = vector.size;
	capacity = vector.capacity;
	arr = vector.arr;
	vector.size = 0;
	vector.capacity = 0;
	vector.arr = nullptr;
	return *this;
}

template <typename Type>
bool operator==(const Vector<Type> &leftVector, const Vector<Type> &rightVector)
{
	if (leftVector.size != rightVector.size) {
		throw SizeDifference("size of vectors isn't equals");
	}
	for (size_t i = 0; i < leftVector.size; i++)
	{
		if (leftVector.arr[i] != rightVector.arr[i])
		{
			return false;
		}
	}
	return true;
}

template <typename Type>
bool operator!=(const Vector<Type> &leftVector, const Vector<Type> &rightVector)
{
	if (leftVector.size != rightVector.size) {
		throw SizeDifference("size of vectors isn't equalse");
	}
	for (size_t i = 0; i < leftVector.size; i++)
	{
		if (leftVector.arr[i] == rightVector.arr[i])
		{
			return false;
		}
	}
	return true;
}

template <typename Type>
bool operator< (const Vector<Type> &leftVector, const Vector<Type> &rightVector)
{
	if (&leftVector == &rightVector) return false;
	for (size_t i = 0; i < (leftVector.size < rightVector.size ? leftVector.size : rightVector.size); i++)
	{
		if (leftVector.arr[i] > rightVector.arr[i]) return false;
		if (leftVector.arr[i] < rightVector.arr[i]) return true;
	}
	if (leftVector.size == rightVector.size) return false;
	else if (leftVector.size < rightVector.size) return true;
	return true;
}

template <typename Type>
bool operator<=(const Vector<Type> &leftVector, const Vector<Type> &rightVector)
{
	if (&leftVector == &rightVector) return true;
	for (size_t i = 0; i < leftVector.size; i++)
	{
		if (leftVector.arr[i] > rightVector.arr[i])
		{
			return false;
		}
	}
	return true;
}

template <typename Type>
bool operator> (const Vector<Type> &leftVector, const Vector<Type> &rightVector)
{
	if (&leftVector == &rightVector) return false;
	for (size_t i = 0; i < leftVector.size; i++)
	{
		if (leftVector.arr[i] < rightVector.arr[i]) return false;
		if (leftVector.arr[i] > rightVector.arr[i]) return true;
	}
	if (leftVector.size == rightVector.size) return false;
	else if (leftVector.size > rightVector.size) return true;
	return true;
}

template <typename Type>
bool operator>=(const Vector<Type> &leftVector, const Vector<Type> &rightVector)
{
	if (&leftVector == &rightVector) return true;
	for (size_t i = 0; i < leftVector.size; i++)
	{
		if (leftVector.arr[i] < rightVector.arr[i])
		{
			return false;
		}
	}
	return true;
}

template <typename T>
Vector<T> operator+(const Vector<T> &leftVector, const Vector<T> &rightVector)
{
	if ((leftVector.size + rightVector.size + leftVector.capacity + rightVector.capacity) > Vector<T>::MAXSIZE) {
		throw IndexOutOfRange("new size of array bigger than MAXSIZE");
	}
	Vector<T> vector(leftVector.size + rightVector.size + leftVector.capacity + rightVector.capacity);
	vector.size = leftVector.size + rightVector.size;
	vector.capacity = leftVector.capacity + rightVector.capacity;
	for (size_t i = 0; i < vector.size; i++)
	{
		if (i < leftVector.size)
		{
			vector.arr[i] = leftVector.arr[i];
		}
		else
		{
			vector.arr[i] = rightVector.arr[i - leftVector.size];
		}
	}
	return vector;
}

template <typename T>
ostream &operator<<(ostream &stream, const Vector<T> &vector)
{
	for (size_t i = 0; i < vector.size; i++)
	{
		stream << vector.arr[i] << " ";
	}
	stream << std::endl;
	return stream;
}

template <typename T>
istream &operator>>(istream &stream, const Vector<T> &vector)
{
	for (size_t i = 0; i < vector.size; i++)
	{
		stream >> vector.arr[i];
	}
	return stream;
}

// резервирует память
template <typename Type>
void Vector<Type>::reserve(size_t n)
{
	if ((n + size) > MAXSIZE) {
		throw IndexOutOfRange("size of array (size and capacity) bigger than MAXSIZE");
	}

	capacity = n;
	Type *temp = new Type[size + capacity];
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = arr[i];
	}
	delete[]arr;

	arr = temp;
	temp = nullptr;
}

// меняет размер вектора
template <typename Type>
void Vector<Type>::resize(const size_t newSize)
{
	if (newSize > MAXSIZE) {
		throw IndexOutOfRange("new size of array bigger than MAXSIZE");
	}
	if (newSize == size) return;

	if (newSize < (capacity + size))
	{
		for (size_t i = size; i < newSize; i++)
		{
			arr[i] = 0;
		}
		capacity = size + capacity - newSize;
		size = newSize;
	}
	else
	{
		capacity = 0;
		Type *temp = new Type[newSize];
		for (size_t i = 0; i < newSize; i++)
		{
			if (i < size)
			{
				temp[i] = arr[i];
			}
			else
			{
				temp[i] = 0;
			}
		}
		delete[]arr;

		size = newSize;
		arr = temp;
		temp = nullptr;
	}
}

template <typename Type>
void Vector<Type>::output()
{
	if (this == nullptr) {
		throw VectorNullPtr("vector isn't init");
	}
	for (size_t i = 0; i < size; i++)
	{
		std::cout << arr[i] << "  ";
	}
	std::cout << endl << "size : " << size << ", capacity : " << capacity << endl;
}

// добавить в конец елемент типа Type
template <typename Type>
void Vector<Type>::pushback(const Type element)
{
	if (size + 1 > MAXSIZE) {
		throw IndexOutOfRange("new size of array bigger than MAXSIZE");
	}
	if (capacity > 0)
	{
		size += 1;
		capacity -= 1;
		arr[size - 1] = element;
	}
	else
	{
		size += 1;
		if ((size + 10) < MAXSIZE)
		{
			capacity = 10;
		}
		Type *temp = new Type[size + capacity];
		for (size_t i = 0; i < size; i++)
		{
			if (i < size - 1)
			{
				temp[i] = arr[i];
			}
			else
			{
				temp[i] = element;
			}
		}
		delete[]arr;

		arr = temp;
		temp = nullptr;
	}
}

// удаляет и возвращает последний элемент
template <typename Type>
Type Vector<Type>::popback()
{
	if (this == nullptr) {
		throw VectorNullPtr("vector isn't init");
	}
	Type temp = arr[size - 1];
	arr[size - 1] = 0;
	size -= 1;
	capacity += 1;
	return temp;
}

template <typename Type>
Vector<Type>::~Vector()
{
	size = 0;
	capacity = 0;
	delete[]arr;
}