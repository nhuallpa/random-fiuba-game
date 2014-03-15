#include <iostream.h>

int Power (int base, unsigned int exponent)
{
	return (exponent <= 0)
    	? 1
		: base * Power(base, exponent - 1);
}


int main (void)
{
	cout << Power(2, 6) << '\n';

	return 0;
}