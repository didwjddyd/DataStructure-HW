#include <iostream>
#include <ctime>
#include <string>

#include "MyDoubleVector.h"

//  Name: ¾çÁ¤¿ë
//  Student ID: 2019203027

using namespace std;

void printVector(MyDoubleVector v, string name)
{
	cout << name << endl;
	cout << "capaciity :" << v.capacity() << " ";
	cout << "size: " << v.size() << endl;

	for (int i = 0; i != v.size(); ++i)
	{
		cout.width(4);
		cout << v[i] << " ";
	}

	cout << endl;
}

int main()
{
	srand(time(NULL));

	MyDoubleVector v1 = MyDoubleVector();
	MyDoubleVector v2 = MyDoubleVector(20);
	MyDoubleVector v3;
	MyDoubleVector v4;

	double dot;

	bool equality;

	cout << "v1 empty: " << v1.empty() << " ";
	cout << "v2 empty: " << v2.empty() << endl;

	for (int i = 0; i != 10; ++i)
	{
		v1.push_back(rand() % 100);
		v2.push_back(rand() % 100);
	}

	printVector(v1, "v1");
	printVector(v2, "v2");

	printVector(v1 + v2, "v1 + v2");
	printVector(v1 - v2, "v1 - v2");

	dot = v1 * v2;
	cout << endl;
	cout << "dot product: " << dot << endl;
	cout << endl;

	v3 = MyDoubleVector(v1);

	printVector(v3, "v3(copy constructor)");

	v4 = v1;
	v1(0);

	v1 += v4;
	printVector(v1, "v1 append");

	v1 = -v1;
	for (int i = 0; i != 10; ++i)
	{
		v1.pop_back();
	}

	printVector(v1, "-v1 pop_back");

	v2(0);

	equality = (v1 == v2);
	cout << endl;
	cout << "v1 == v2: " << equality << endl;
	cout << endl;

	v1.clear();

	printVector(v1, "v1 clear");

	return 0;
}