#pragma once
#ifndef __ARRAY_H
#define __ARRAY_H

#include <iostream>
#include <string>
using namespace std;


/*
T should have:
1. operator =
2. operator <<
3. defualt c'tor
*/
template <class T>
class Array
{
private:
	//attributes
	int logicalSize;
	int phyisicalSize;
	char delimiter;
	T* arr;

public:
	//constructor function
	Array(int size = 0, char delimiter = ' ');
	Array(const Array & other);
	~Array();

	// operators assignment, add and []
	const Array& operator=(const Array<T> & other);
	const Array& operator+(const T & newValue);
	T & operator[](int index);


	// get functions
	const Array<T> getArray() const;
	int getPhysicalSize()     const;
	int getLogicalSize()      const;
	char getDelimiter()       const;

	friend ostream& operator<<(ostream & os, const Array& arr)
	{
		for (int i = 0; i < arr.logicalSize; i++)
		{
			os << arr[i] << arr.delimiter;
		}
		return os;
	}

};


template <class T>
Array<T>::Array(int maxSize, char delimiter) : phyisicalSize(maxSize), logicalSize(0), delimiter(delimiter)
{
	arr = new T[phyisicalSize];
}

template <class T>
Array<T>::Array(const Array<T> & other) : arr(NULL)
{
	*this = other;
}

template <class T>
Array<T>::~Array()
{
	delete[]arr;
}

template <class T>
const Array& Array<T>::operator=(const Array & other)
{
	if (this != &other)
	{
		delete[]arr;
		phyisicalSize = other.phyisicalSize;
		logicalSize = other.logicalSize;
		delimiter = other.delimiter;
		arr = new T[phyisicalSize];
		for (int i = 0; i < logicalSize; i++)
		{
			arr[i] = other[i];
		}
	}
	return *this;
}

template <class T>
const Array& Array<T>::operator+(const T & newValue)
{
	if (phyisicalSize > logicalSize)
	{
		arr[logicalSize] = newValue;
	}
	else
	{
		phyisicalSize++;
		T * newArray = arr;
		newArray[logicalSize] = newValue;
		logicalSize++;
		delete[]arr;
		arr = newArray;
	}
	return *this;
}

template <class T>
T& Array::operator[](int index)
{
	return arr[index];
}

template <class T>
const Array<T> Array::getArray() const
{
	return arr;
}

template <class T>
int Array::getPhysicalSize() const
{
	return phyisicalSize;
}

template <class T>
int Array::getLogicalSize() const
{
	return logicalSize;
}

template <class T>
char Array::getDelimiter() const
{
	return delimiter;
}

#endif


