#include <iostream>
#pragma warning(disable:4996)
using namespace std;

int foo(int* vector, int firstIndex, int lastIndex, int elementSearched)
{
	int middleElement;
	if (firstIndex > lastIndex)
	{
		middleElement = -1;
	}
	else
	{
		middleElement = (firstIndex + lastIndex) / 2;
		if (elementSearched < vector[middleElement])
		{
			middleElement = foo(vector, firstIndex, lastIndex - 1, elementSearched);
		}
		else if (elementSearched > vector[middleElement])
		{
			middleElement = foo(vector, firstIndex + 1, lastIndex, elementSearched);
		}
	}
	return middleElement;
}

void main()
{
	int size = 200;
	int* vector = new int[size];
	for (int i = 0; i < size; i++)
	{
		vector[i] = i;
	}
	int searchElement = 144;
	int found = foo(vector, vector[0], vector[size - 1], searchElement);
	found == -1 ?
		cout << "Element does not exist in vector!" << endl :
		cout << "Element is in vector!" << endl;
	delete[] vector;
	system("pause");
}