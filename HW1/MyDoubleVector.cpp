#include <algorithm>
#include <cassert>

#include "MyDoubleVector.h"

//  Name: ¾çÁ¤¿ë
//  Student ID: 2019203027

//  constructors
MyDoubleVector::MyDoubleVector(size_t init_capacity)
{
	data = new double[init_capacity];
	vector_capacity = init_capacity;
	vector_size = 0;
}

MyDoubleVector::MyDoubleVector(const MyDoubleVector& v)
{
	data = new double[v.vector_capacity];
	vector_capacity = v.vector_capacity;
	vector_size = v.vector_size;
	std::copy(v.data, v.data + vector_size, data);
}

//  desturctor
MyDoubleVector::~MyDoubleVector()
{
	delete[] data;
}

//  binary operators
MyDoubleVector& MyDoubleVector::operator =(const MyDoubleVector& source)
{
	if (this == &source)
	{
		return *this;
	}

	if (vector_capacity != source.vector_capacity)
	{
		delete[] data;
		data = new double[source.vector_capacity];
		vector_capacity = source.vector_capacity;
	}

	vector_size = source.vector_size;
	std::copy(source.data, source.data + source.vector_size, data);

	return *this;
}

void MyDoubleVector::operator += (const MyDoubleVector& operand)
{
	for (size_t i = 0; i != operand.size(); ++i)
	{
		push_back(operand[i]);
	}
}

double& MyDoubleVector::operator [](int index)
{
	assert(index <= vector_size);
	return data[index];
}

double& MyDoubleVector::operator [](int index) const
{
	assert(index <= vector_size);
	return data[index];
}

MyDoubleVector MyDoubleVector::operator +(const MyDoubleVector& v)
{
	assert(v.size() == vector_size);

	MyDoubleVector result = MyDoubleVector(vector_size);

	for (size_t i = 0; i != vector_size; ++i)
	{
		result.push_back(data[i] + v[i]);
	}

	return result;
}

MyDoubleVector MyDoubleVector::operator -(const MyDoubleVector& v)
{
	assert(v.size() == vector_size);

	MyDoubleVector result = MyDoubleVector(vector_size);

	for (size_t i = 0; i != vector_size; ++i)
	{
		result.push_back(data[i] - v[i]);
	}
	
	return result;
}

double MyDoubleVector::operator *(const MyDoubleVector& v)
{
	assert(v.size() == vector_size);

	double result = 0;

	for (size_t i = 0; i != vector_size; ++i)
	{
		result += data[i] * v[i];
	}

	return result;
}

bool MyDoubleVector::operator ==(const MyDoubleVector& v)
{
	if (vector_size != v.size())
	{
		return false;
	}

	for (size_t i = 0; i != vector_size; ++i)
	{
		if (data[i] != v[i])
		{
			return false;
		}
	}

	return true;
}

//  unary operators
MyDoubleVector MyDoubleVector::operator -()
{
	MyDoubleVector result = MyDoubleVector(vector_size);

	for (size_t i = 0; i != vector_size; ++i)
	{
		result.push_back(-data[i]);
	}

	return result;
}

void MyDoubleVector::operator ()(double x)
{
	for (size_t i = 0; i != vector_size; ++i)
	{
		data[i] = x;
	}
}

//  member functions
void MyDoubleVector::pop_back()
{
	vector_size--;
}

void MyDoubleVector::push_back(double x)
{
	if (vector_size == vector_capacity)
	{
		reserve(vector_size * 2);
	}

	data[vector_size] = x;
	vector_size++;
}

size_t MyDoubleVector::capacity() const
{
	return vector_capacity;
}

size_t MyDoubleVector::size() const
{
	return vector_size;
}

void MyDoubleVector::reserve(size_t n)
{
	if (n == vector_capacity)
	{
		return;
	}

	if (n < vector_size)
	{
		n = vector_size;
	}

	double *new_data = new double[n];
	std::copy(data, data + vector_size, new_data);
	delete[] data;
	data = new_data;
	vector_capacity = n;
}

bool MyDoubleVector::empty() const
{
	return vector_size == 0;
}

void MyDoubleVector::clear()
{
	vector_size = 0;
}