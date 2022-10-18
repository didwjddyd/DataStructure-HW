#ifndef MY_DOUBLE_VECTOR_H
#define MY_DOUBLE_VECTOR_H

#include <cstdlib>

//  Name: ¾çÁ¤¿ë
//  Student ID: 2019203027

class MyDoubleVector {
public:
	static const size_t Default_Capacity = 100;
	
	//  constructors
	MyDoubleVector(size_t init_capacity = Default_Capacity);  //  default
	//  Precondition: init_capacity >= 0
	//  Postcondition: Create a MyDoubleVector object 
	//  have double dynamic array with size of init_capacity

	MyDoubleVector(const MyDoubleVector& v);  //  for deep copy
	//  Precondition: MyDoubleVector you want to copy
	//  Postcondition: Create a MyDoubleVector object
	//  have member variable with value of parameter's member variable

	//  destructor
	~MyDoubleVector();
	//  Precondition: none
	//  Postcondition: delete MyDoubleVector object

	//  binary operators
	MyDoubleVector& operator =(const MyDoubleVector& source);
	//  Precondition: MyDoubleVector you want to copy
	//  Postcondition: Return a MydoubleVector reference and copy parameter's member variables

	void operator +=(const MyDoubleVector& operand);
	//  Precondition: MyDoubleVector you want to append to LHS with any capacity
	//  Postcondition: Append data of RHS to LHS and resize LHS's size variable

	double& operator [](int index);
	//  Precondition: index <= vector_size
	//  Postcondition: Return double reference of data[index]

	double& operator [](int index) const;
	//  Precondition: index <= vector_size
	//  Postcondition: Return const MyDoubleVector reference's double reference of data[index]

	MyDoubleVector operator +(const MyDoubleVector& v);
	//  Precondition: LHS's vector_size == RHS's vector_size
	//  Postcondition: Return MyDoubleVector object have vector sum of operands

	MyDoubleVector operator -(const MyDoubleVector & v);
	//  Precondition: LHS's vector_size == RHS's vector_size
	//  Postcondition: Return MyDoubleVector object have vector difference of operands

	double operator *(const MyDoubleVector& v);
	//  Precondition: LHS's vector_size == RHS's vector_size
	//  Postcondition: Return MyDoubleVector object have dot product of operands

	bool operator ==(const MyDoubleVector& v);
	//  Precondition: MyDoubleVector want to compare
	//  Postcondition: Return true if operands are same

	//  unary operators
	MyDoubleVector operator -();
	//  Precondition: none
	//  Postcondition: Return MyDoubleVector operand's each elements are multiplied by -1

	void operator ()(double x);
	//  Precondition: parameter x's type is double
	//  Postcondition: Make all of operand's elements to x

	//  member functions
	void pop_back();  
	//  Precondition: none
	//  Postcondition: Remove the last element
	
	void push_back(double x);  
	//  Precondition: parameter x's type is double
	//  Postcondition: Add a new element at the end of the vector
	
	size_t capacity() const; 
	//  Precondition: none
	//  Postcondition: Return storage space for the elements

	size_t size() const; 
	//  Precondition: none
	//  Postcondition: Return numbers of elements
	
	void reserve(size_t n); 
	//  Precondition: n > 0
	//  Postcondition: Request more capacity if vector_capacity < n

	bool empty() const; 
	//  Precondition: none
	//  Postcondition: Return true if vector_size is 0

	void clear();
	//  Precondition: none
	//  Postcondition: Remove all the elements and make vector_size to 0

private:
	double* data;
	size_t vector_capacity;  //  storage space for the elements
	size_t vector_size;  //  number of elements
};

#endif