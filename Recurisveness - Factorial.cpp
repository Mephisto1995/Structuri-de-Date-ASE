#include <iostream>
#pragma warning(disable:4996)
using namespace std;

int foo(int number)
{
	int retVal;
	if (number == 0)
	{
		retVal = 1;
	}
	else
	{
		retVal = number * foo(number - 1);
	}
	return retVal;
}

void main()
{
	int number = 4;
	int retVal = foo(number);
	cout << "Factorial: " << retVal << endl;
	system("pause");
}