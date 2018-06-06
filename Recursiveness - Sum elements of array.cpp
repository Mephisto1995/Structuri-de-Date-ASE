#include <iostream>
#pragma warning(disable:4996)
using namespace std;

int foo(int* vector, int size)
{
	int sum;
	if (size == 0)
	{
		sum = 0;
	}
	else
	{
		sum = vector[size - 1] + foo(vector, size - 1);
	}
	return sum;
}

void main()
{
	int size = 5;
	int* vector = new int[size];
	for (int i = 0; i < size; i++)
	{
		vector[i] = i;
	}
	int sum = foo(vector, size);
	cout << "Sum of the vector's elements is: " << sum << endl;
	delete[] vector;
	system("pause");
}