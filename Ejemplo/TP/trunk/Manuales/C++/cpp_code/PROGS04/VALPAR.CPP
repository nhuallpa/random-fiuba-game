#include <iostream.h>

void Foo (int num)
{
	num = 0;
	cout << "num = " << num << '\n';
}

int main (void)
{
	int x = 10;

	Foo(x);
	cout << "x = " << x << '\n';
	return 0;
}