#include <iostream.h>

template <class Type>
void Swap (Type &x, Type &y)
{
	Type tmp = x;
	x = y;
	y = tmp;
}

int main (void)
{
	int a = 1.2;
    int b = 2.2;

    cout << a << ' ' << b << '\n';
    Swap(a, b);
    cout << a << ' ' << b << '\n';
}