#include <iostream.h>

void Swap1 (int x, int y)
{
	int temp = x;
	x = y;
	y = temp;
}

void Swap2 (int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void Swap3 (int &x, int &y)
{
	int temp = x;
	x = y;
	y = temp;
}

int main (void)
{
	int i = 10, j = 20;

    Swap1(i, j);
	cout << i << ", " << j << '\n';
	Swap2(&i, &j);
	cout << i << ", " << j << '\n';
	Swap3(i, j);
	cout << i << ", " << j << '\n';
    return 0;
}