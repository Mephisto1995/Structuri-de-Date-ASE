#include <iostream>
#pragma warning(disable:4996)
using namespace std;

int foo(int n, int k)
{
	int sum;
	if (k > n)
	{
		sum = 0;
	}
	else if (k == 0 || k == n)
	{
		sum = 1;
	}
	else
	{
		sum = foo(n - 1, k) + foo(n - 1, k - 1);
	}
	return sum;
}

void main()
{
	int n = 7, k = 0; // Combinari de 4(n) luate cate 3(k);
	int combinari = foo(n, k);
	cout << "Combinari: " << combinari << endl;
	system("pause");
}